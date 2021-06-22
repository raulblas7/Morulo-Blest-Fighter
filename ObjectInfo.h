#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>

//Informacion esencial para gestionar los envios y recepciones de mensajes
struct ObjectInfo
{
  SDL_Rect rect;
  Vector2D dir;
  float angle;
  char colNick[12];
};