#pragma once

#include "GameObject.h"

class Player : public GameObject
{

private:
  // seriali
  uint8_t points;
  //no serializar

public:
  Player(uint8_t goType);
  virtual ~Player();
  // Se encarga de gestionar el imput del player
  virtual void update(float deltaTime) override;
  virtual void to_bin();
  virtual int from_bin(char *data);
};
