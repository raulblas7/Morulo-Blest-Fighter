#include "Player.h"
#include "GameMessage.h"

Player::Player(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
    //rect = new SDL_Rect();
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

Vector2D Player::getPlayerPos(){
    return pos;
}