#include "Player.h"
#include "Constants.h"

Player::Player(uint8_t type_, std::string id_, float angle_, bool act, Texture *texture_, SDL_Rect rect_) : GameObject(type_, id_, angle_, act, texture_, rect_)
{
	dir = Vector2D(10, 10);
	points = 0;
	kills = 10;
	deaths = 15;
	SIZE_SERIALIZABLE += SIZE_PLAYER;
}
Player::Player() : GameObject()
{
	dir = Vector2D(10, 10);
	points = 0;
	kills = 100;
	deaths = 0;
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
	if (texture != nullptr)
		texture->render(rect, SDL_FLIP_NONE);
}

void Player::to_bin()
{
	std::cout << "Entra to_bin Player\n";

	GameObject::to_bin();

	cout << "TMP" << sizeof(tmp) << endl;

	memcpy(tmp, &index, sizeof(uint8_t));
	tmp += sizeof(index);
	std::cout << "Index:" << (int)index << endl;

	memcpy(tmp, &points, sizeof(uint8_t));
	tmp += sizeof(points);
	std::cout << "Points:" << (int)points << endl;

	memcpy(tmp, &kills, sizeof(uint8_t));
	tmp += sizeof(kills);
	std::cout << "Kills:" << (int)kills << endl;

	memcpy(tmp, &deaths, sizeof(uint8_t));
	tmp += sizeof(deaths);
	std::cout << "Deaths:" << (int)deaths << endl;

	memcpy(tmp, &dir, sizeof(Vector2D));
	tmp += sizeof(dir);
	std::cout << "Dir:" << dir.getX() << dir.getY() << endl;

	std::cout << "Sale to_bin Player\n";
	std::cout << "Tamaño esperado  " << sizeof(Player) << " Tamaño final es " << sizeof(tmp) * sizeof(_data) << "\n";
}

int Player::from_bin(char *data)
{
	std::cout << "Entra from_bin player\n";

	/*alloc_data(SIZE_PLAYER);
	memcpy(static_cast<void *>(_data), data, SIZE_PLAYER);
	std::cout << "Size" << SIZE_PLAYER + SIZE_SERIALIZABLE << endl;
*/

	char *pos = data;

	memcpy((void *)&index, tmp, sizeof(index));
	pos += sizeof(index);
	std::cout << "Index:" << (int)index << endl;

	memcpy((void *)&points, tmp, sizeof(points));
	pos += sizeof(points);
	std::cout << "Points:" << (int)points << endl;

	memcpy((void *)&kills, tmp, sizeof(kills));
	pos += sizeof(kills);
	std::cout << "Kills:" << (int)kills << endl;

	memcpy((void *)&deaths, tmp, sizeof(deaths));
	pos += sizeof(deaths);
	std::cout << "Deaths:" << (int)deaths << endl;

	memcpy((void *)&dir, tmp, sizeof(dir));
	pos += sizeof(dir);
	std::cout << "Dir:" << dir.getX() << " " << dir.getY() << endl;

	//_size += SIZE_PLAYER;
	std::cout << "Sale from_bin Player\n";
	std::cout << "Tamaño esperado " << sizeof(Player) << " Tamaño final es " << sizeof(tmp) * sizeof(_data) << "\n";

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

void Player::setDir(Vector2D d)
{
	dir = d;
}

void Player::onCollisionEnter(GameObject *other)
{
	/*if (other->type == ObjectType::BULLET)
    {
        Bullet *bullet = (Bullet *)other;
        if (bullet->index == index)
            return;
        //hasToRespawn = true;
    }*/
}
/*//accedemos al size del padre
	size_t sizeGO = GameObject::size()-SIZE_PLAYER;
	//buffer auxiliar
	char buffer[sizeGO];
	//copiamos la data del padre en el buffer auxiliar
	memcpy(buffer, GameObject::data(), sizeGO);*/

//almacenamiento para la data
//alloc_data(sizeGO + SIZE_PLAYER);

/*//char *tmp = _data;
	memcpy(tmp, buffer, sizeGO);
	//avanzamos el size del padre ya que ya se ha hecho en el to bin de GameObject
	tmp += sizeGO;*/