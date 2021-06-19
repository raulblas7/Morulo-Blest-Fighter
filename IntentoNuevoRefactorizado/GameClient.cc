#include "GameClient.h"

GameClient::GameClient(const std::string &nick, const char *host, const char *port) : window(nullptr), nick(nick), socket(host, port), terminated(false), world(nullptr)
{
}

GameClient::~GameClient()
{
}

// Public methods

void GameClient::init()
{
    int winX, winY; // PosiciOn de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// InicializaciOn del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("MoruloBlestFighter", winX, winY, SCREEN_WIDTH,
							   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == NULL || renderer_ == NULL)
	{
		std::cout << "Game window or renderer was null \n";
	}

    world = new GameWorld(window);

    netThread = new sf::Thread(&GameClient::recieveMessage, this);
    netThread->launch();

    // Login
    login();
}

void GameClient::run()
{
    while (!terminated && window->isOpen())
    {
        if (!processEvents())
            break;
    }
}

void GameClient::close()
{
    // Logout
    logout();

    terminated = true;
    netThread->wait();

    delete world;
    delete netThread;
    delete window;
}

void GameClient::recieveMessage()
{
    while (!terminated)
    {
        MessageServer message;
        socket.recv(message);

        if (message.type == MessageServer::LOGIN)
        {
            if (message.index == -1)
            {
                printf("Partida llena\n");
                terminated = true;
                break;
            }
            playerState.index = message.index;
            world->setIndex(message.index);
        }

        if (message.type == MessageServer::LOGOUT)
        {
            printf("Conexion cerrada\n");
            terminated = true;
            break;
        }

        world->copy(message.world);
        world->render();
    }
}

void GameClient::login()
{
    MessageGameClient message(nick, playerState);
    message.type = MessageGameClient::LOGIN;
    message.playerState = playerState;

    socket.send(message, socket);
}

void GameClient::logout()
{
    MessageGameClient message(nick, playerState);
    message.type = MessageGameClient::LOGOUT;
    message.playerState = playerState;

    socket.send(message, socket);
}

bool GameClient::processEvents()
{
    sf::Event event;
    bool processed = false;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return false;
        processed = !playerState.handleEvent(event) || processed;
    }

    if (processed)
    {
        MessageGameClient messageGameClient;
        messageGameClient.type = MessageGameClient::MESSAGE;
        messageGameClient.nick = nick;
        messageGameClient.playerState = playerState;

        socket.send(messageGameClient, socket);
    }

    return true;
}
