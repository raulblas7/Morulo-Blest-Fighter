#include "SDLGame.h"
#include "iostream"
#include <SDL2/SDL.h>
#include "Resources.h"
using namespace std;

SDLGame* SDLGame::instance = nullptr;

SDLGame::SDLGame(){
    initGame();
//	initResources();
}

SDLGame::~SDLGame()
{
	delete textureManager_;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	SDL_Quit();
}

void SDLGame::initGame()
{
	int winX, winY; // PosiciOn de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// InicializaciOn del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("MoruloBlestFighter", winX, winY, _WINDOW_WIDTH_,
							   _WINDOW_HEIGHT_, SDL_WINDOW_SHOWN);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == NULL || renderer_ == NULL)
	{
		std::cout << "Game window or renderer was null \n";
	}
}

SDLGame *SDLGame::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SDLGame();
	}
	return instance;
}

void SDLGame::initResources()
{
	//Crear e inicializar textureManager
	textureManager_ = new TexturesManager();
	textureManager_->init();

	//Creacion de las texturas
	for (auto &image : Resources::images_)
	{
		textureManager_->loadFromImg(image.id, renderer_, image.fileName);
	}
}
