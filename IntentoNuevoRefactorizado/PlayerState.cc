#include "PlayerState.h"
#include "InputHandler.h"

PlayerState::PlayerState() : index(-1), xDirection(0), yDirection(0)
{
}

PlayerState::~PlayerState()
{
}

bool PlayerState::handleEvent()
{
    PlayerState copy = *this;

    InputHandler::instance()->update();

    //Movimiento por teclado del jugador
    if (InputHandler::instance()->keyDownEvent())
    {
        if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_UP)))
        {
            yDirection = -1;
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_DOWN)))
        {
            yDirection = 1;
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            xDirection = 1;
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            xDirection = -1;
        }
    }
    else if (InputHandler::instance()->keyUpEvent())
    {
        if (InputHandler::instance()->isKeyUp(SDL_Keycode(SDLK_UP)))
        {
            yDirection = 0;
        }
        else if (InputHandler::instance()->isKeyUp(SDL_Keycode(SDLK_DOWN)))
        {
            yDirection = 0;
        }
        else if (InputHandler::instance()->isKeyUp(SDL_Keycode(SDLK_RIGHT)))
        {
            xDirection = 0;
        }
        else if (InputHandler::instance()->isKeyUp(SDL_Keycode(SDLK_LEFT)))
        {
            xDirection = 0;
        }
    }

    return copy == *this;
}