#include "Player.h"
#include "GameMessage.h"
#include "Texture.h"

Player::Player(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
}

Player::~Player()
{
    
}

void Player::update()
{
}

void Player::logout()
{
}

void Player::initPlayer()
{
    //conectarse al servidor mediante login
    //Mandamos el mensaje de LOGIN
    GameMessage logMsg = GameMessage(MessageType::LOGIN, this);
    if (socket.send(logMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

Socket* Player::getPlayerSocket(){
    return &socket;
    
}

void Player::setPosition(const Vector2D& newPos){
    pos = newPos;
}

void Player::setTam(int newTam){
    tam = newTam;
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

int Player::getPlayerTam(){
    return tam;
}
