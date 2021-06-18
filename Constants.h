#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "stdbool.h"

//	Ancho de la ventana
#define SCREEN_WIDTH 640
//	Altura de la ventana
#define SCREEN_HEIGHT 480
//	TODO
#define FRAME_TIME 16666
//	Máxima velocidad en y
#define MAX_VERTICAL_SPEED 25
//	Máxima velocidad en x
#define MAX_HORIZONTAL_SPEED 25
//	Velocidad del player
#define PLAYER_SPEED 2
//	Ancho de la textura del jugador
#define PLAYER_WIDTH 60
//	Altura de la textura del jugador
#define PLAYER_HEIGHT 60
//	Posición en x inicial del jugador 1
#define PLAYER1_POSX 320
//	Posición en y inicial del jugador 1
#define PLAYER1_POSY 100
//	Posición en x inicial del jugador 2
#define PLAYER2_POSX 320
//	Posición en y inicial del jugador 2
#define PLAYER2_POSY 380
//	Tamaño en y de la bala
#define BULLET_HEIGHT 8
//	Tamaño en x de la bala
#define BULLET_WIDTH 8
//	Máximo número de jugadores permitidos en el juego
#define MAX_PLAYERS 2
//	Frame rate del cliente
#define CLIENT_FRAME_TIME 15
//	Frame rate del servidor
#define SERVER_FRAME_TIME 15

#endif