#include "Bullet.h"
#include "GameMessage.h"
#include "Texture.h"
#include "Constants.h"


Bullet::Bullet(const char *s, const char *p, const char *n) : socket(s, p), nick(n)
{
    dir = Vector2D(0,0);
    vel = 4.0f;
}

Bullet::~Bullet()
{
    
}

void Bullet::update()
{

}

void Bullet::logout()
{

}

void Bullet::initBullet()
{
    //conectarse al servidor mediante login
    //Mandamos el mensaje de LOGIN
    GameMessage logMsg = GameMessage(MessageType::LOGIN, this);
    if (socket.send(logMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de login\n";
    }
}

SDL_Rect Bullet::getBulletRect(){
    return rect;
}

void Bullet::setBulletRect(const SDL_Rect& newRect){
    rect = newRect;
}

Socket* Bullet::getBulletSocket(){
    return &socket;
}

void Bullet::setTexture(Texture* newTexture){
    texture =newTexture;
}

Texture* Bullet::getBulletTexture(){
    return texture;
}

bool Bullet::checkLimits(){
    return pos.getX() > tam && pos.getY() < SCREEN_HEIGHT - tam && pos.getX() < SCREEN_WIDTH - tam && pos.getY() > tam;
}
