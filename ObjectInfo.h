#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>

struct ObjectInfo
{
  // Vector2D pos;
  // int tam;
  SDL_Rect rect;
  Vector2D dir;
  float angle;
};