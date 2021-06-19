#include "Player.h"
#include "GameMessage.h"
#include "Constants.h"
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

void Player::render()
{
}

void Player::to_bin()
{
	GameObject::to_bin();

	//accedemos al size del padre
	size_t sizeGO = GameObject::size();
	//buffer auxiliar
	char buffer[sizeGO];
	//copiamos la data del padre en el buffer auxiliar
	memcpy(buffer, GameObject::data(), sizeGO);
	//almacenamiento para la data
	alloc_data(sizeGO + SIZE_PLAYER);

	char *tmp = _data;
	memcpy(tmp, buffer, sizeGO);
	//avanzamos el size del padre ya que ya se ha hecho en el to bin de GameObject
	tmp += sizeGO;

	memcpy(tmp, &index, sizeof(index));
    tmp += sizeof(index);

	memcpy(tmp, &points, sizeof(uint8_t));
	tmp += sizeof(points);

	memcpy(tmp, &kills, sizeof(uint8_t));
	tmp += sizeof(kills);

	memcpy(tmp, &deaths, sizeof(uint8_t));
	tmp += sizeof(deaths);

	memcpy(tmp, &dir, sizeof(Vector2D));
	tmp += sizeof(dir);
}

int Player::from_bin(char *data)
{
	GameObject::from_bin(data);

	char *tmp = data;
    tmp += GameObject::size();

    memcpy(&index, tmp, sizeof(index));
	tmp += sizeof(index);

	memcpy(&points, tmp, sizeof(points));
    tmp += sizeof(points);

	memcpy(&kills, tmp, sizeof(kills));
    tmp += sizeof(kills);

	memcpy(&deaths, tmp, sizeof(deaths));
    tmp += sizeof(deaths);

	memcpy(&dir, tmp, sizeof(dir));
    tmp += sizeof(dir);

	_size += SIZE_PLAYER;

	return 0;
}

bool Player::canMove()
{
	bool move = false;
	if (rect.x + (dir.getX() * PLAYER_SPEED) > 0 && rect.x + (dir.getX() * PLAYER_SPEED) < SCREEN_WIDTH)
	{
		rect.x += dir.getX() * PLAYER_SPEED;
		move = true;
	}
	if (rect.y + (dir.getY() * PLAYER_SPEED) > 0 && rect.y + (dir.getY() * PLAYER_SPEED) < SCREEN_HEIGHT)
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

void Player::setDir(Vector2D d)
{
	dir = d;
}

void Player::render()
{
	// texture->render(rect);
}



void Player::onCollisionEnter(GameObject *other)
{
    if (other->type == ObjectType::BULLET)
    {
        Bullet *bullet = (Bullet *)other;
        if (bullet->index == index)
            return;
        //hasToRespawn = true;
    }
}