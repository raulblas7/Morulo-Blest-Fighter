#include "Bullet.h"
#include "GameMessage.h"
#include "Texture.h"
#include "Constants.h"


Bullet::Bullet(Socket socket_, Vector2D dir_, SDL_Rect rect_, std::string nick_) : socket(socket_), dir(dir_), rect(rect_), nick(nick_)
{
    vel = 4.0f;
    initBullet();
}

Bullet::~Bullet()
{
    
}

void Bullet::update()
{
    if(checkLimits()){
        rect.x += vel * dir.getX();
        rect.y += vel * dir.getY();
    }
    else{
        shouldDelete = true;
    }
}

void Bullet::initBullet()
{
    //conectarse al servidor mediante login
    //Mandamos el mensaje de LOGIN
    GameMessage bMsg = GameMessage(MessageType::NEWBULLET, this);
    if (socket.send(bMsg, socket) == -1)
    {
        std::cout << "Error al enviar el mensaje de newBullet\n";
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
    return rect.x + rect.w < SCREEN_WIDTH && rect.x > 0 && rect.y + rect.h < SCREEN_HEIGHT && rect.y > 0;
}
