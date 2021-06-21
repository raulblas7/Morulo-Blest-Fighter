#include "Player.h"
#include "GameMessage.h"
#include "Texture.h"
#include "Constants.h"
#include <math.h>


Player::Player(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
    dir = Vector2D(0,0);
    vel = 10.0f;
}

Player::~Player()
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

void Player::setTexture(Texture* newTexture){
    texture =newTexture;
}

Texture* Player::getPlayerTexture(){
    return texture;
}

bool Player::canMove(){
    return rect.x > rect.w && rect.y < SCREEN_HEIGHT - rect.h && rect.x < SCREEN_WIDTH - rect.w && rect.y > rect.h;
}

Vector2D Player::getPointToShoot(){
    
    Vector2D posToShoot;
    if(angle == 0 or angle == 360){
        posToShoot.setX(rect.x + rect.w);
        posToShoot.setY(rect.y + (rect.h / 2));
        return posToShoot;
    }
    else if(angle == 90 or angle == -270){
        posToShoot.setX(rect.x + (rect.w / 2));
        posToShoot.setY(0);
        return posToShoot;
    }
    else if(angle == 180 or angle == -180){
        posToShoot.setX(0);
        posToShoot.setY(rect.y + (rect.h / 2));
        return posToShoot;
    }
    else {
        posToShoot.setX(rect.x + (rect.w / 2));
        posToShoot.setY(rect.y + rect.h);
        return posToShoot;
    }
}

void Player::setRotate(float angle_) { this->angle = angle_; }