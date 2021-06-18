#include "Player.h"
#include "GameMessage.h"
#include "Constants.h"
//#include "InputHandler.h"

Player::Player(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
	rect = SDL_Rect();
	rect.x = PLAYER1_POSX;
	rect.y = PLAYER1_POSY;
	rect.w = PLAYER_WIDTH;
	rect.h = PLAYER_HEIGHT;

	dir = Vector2D(0, 0);

	std::cout << nick << std::endl;
}

Player::~Player()
{
	//texture->~Texture();
}

void Player::update()
{
	//  Movimiento
	//checkInput();
	//checkPos();
	//  CheckColls
	//  Disparar
}

bool Player::canMove()
{
	bool move = false;
	if (rect.x + (dir.getX() * PLAYER_SPEED) > 0 && rect.x + (dir.getX() * PLAYER_SPEED) < SCREEN_WIDTH)
	{
       rect.x += dir.getX() * PLAYER_SPEED;
	   move = true;
	}
   	if(rect.y + (dir.getY() * PLAYER_SPEED) > 0 && rect.y + (dir.getY() * PLAYER_SPEED) < SCREEN_HEIGHT)
   	{
       rect.y += dir.getY() * PLAYER_SPEED;
	   move = true;
   	}
	return move;	
}

void Player::initPlayer()
{
	//conexion al server
	std::string msg;
	GameMessage em(nick, this);
	em.type = GameMessage::LOGIN;

	if (socket.send(em, socket) == -1)
	{
		perror("Fallo enviando el mensaje de login del jugador");
	}
}

Socket *Player::getPlayerSocket()
{
	return &socket;
}

void Player::setTexture(Texture *newTexture)
{
	texture = newTexture;
}

Texture *Player::getPlayerTexture()
{
	return texture;
}

SDL_Rect Player::getPlayerRect()
{
	return rect;
}

void Player::setDir(Vector2D d){
	dir = d;
}