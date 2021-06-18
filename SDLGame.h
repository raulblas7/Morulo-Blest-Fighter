#pragma once

#include <SDL2/SDL.h>
#include "TexturesManager.h"

class SDLGame
{

public:
  static SDLGame *GetInstance();

  SDLGame(SDLGame &other) = delete;
  void operator=(const SDLGame &) = delete;

  void start();

  TexturesManager *getTextureManager() const { return textureManager_; }
  SDL_Window *getWindow() const { return window_; };
  SDL_Renderer *getRenderer() const { return renderer_; };
  ~SDLGame();
  SDLGame();

private:
  void initGame();
  void initResources();
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  TexturesManager *textureManager_ = nullptr;

  static SDLGame *instance;

  const static int _WINDOW_WIDTH_ = 640;
  const static int _WINDOW_HEIGHT_ = 480;
};