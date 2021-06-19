#include "Player.h"
#include "GameMessage.h"
#include "Constants.h"
//#include "InputHandler.h"
#include "Resources.h"
#include "SDLGame.h"
Player::Player() 
{
	rect = SDL_Rect();
	rect.x = PLAYER1_POSX;
	rect.y = PLAYER1_POSY;
	rect.w = PLAYER_WIDTH;
	rect.h = PLAYER_HEIGHT;

	dir = Vector2D(0, 0);
   // texture = SDLGame::GetInstance()->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture);
}

Player::~Player()
{
	//texture->~Texture();
}

void Player::update(float deltaTime)
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


void Player::render(){
   // texture->render(rect);
}


void Player::to_bin(){
   // texture->render(rect);
}

int Player::from_bin(char *data){
    //texture->render(rect);
	return 0;
}
