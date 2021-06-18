#include "Player.h"
#include "GameMessage.h"
#include "Constants.h"

Player::Player(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
    rect = SDL_Rect();
    rect.x = 100;
    rect.y = 100;
    rect.w = PLAYER_WIDTH;
    rect.h = PLAYER_HEIGHT;
}

Player::~Player()
{
    texture->~Texture();
}

void Player::update()
{
    //  Movimiento 
    //  CheckColls
    //  Disparar
}

void Player::initPlayer()
{
    //conexion al server
    std::string msg;
    GameMessage em(nick, this);
    em.type = GameMessage::LOGIN;
    
    if (socket.send(em, socket) == -1)
    {
        perror("Fallo enviando el mensaje de login del jugador");
    }
}

Socket* Player::getPlayerSocket(){
    return &socket;
}

void Player::setPosition(const Vector2D& newPos){
    pos = newPos;
}

void Player::setTexture(Texture* newTexture){
    texture =newTexture;
}

Texture* Player::getPlayerTexture(){
    return texture;
}

SDL_Rect Player::getPlayerRect(){
    return rect;
}

Vector2D Player::getPlayerPos(){
    return pos;
}