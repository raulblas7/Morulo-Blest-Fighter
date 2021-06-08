#pragma once

#include "GameObject.h"

class Player : public GameObject
{

private:
  //seriali
  uint8_t points;
  //no serializar

public:
  Player();
  virtual ~Player();

  virtual void to_bin();
  virtual int from_bin(char *data);
};
