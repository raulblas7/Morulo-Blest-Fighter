#include "MoruloBlestFighter.h"
#include <assert.h>
#include "SDL_macros.h"
#include <iostream>

#include "SDLGame.h"
#include "InputHandler.h"
using namespace std;

MoruloBlestFighter::MoruloBlestFighter()
{

    game_ = nullptr;
    //mngr_=(nullptr);
    exit_ = false;
    initGame();
}

MoruloBlestFighter::~MoruloBlestFighter()
{
    closeGame();
}

void MoruloBlestFighter::initGame()
{


    game_ = SDLGame::init("MoruloBlestFighter", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

    /// AsteroidPool::init();
    //BulletsPool::init();
    textureManager = new TexturesManager();
    fontManager = new FontsManager();

    // mngr_ = new Manager(game_);
    // renderSystem_ = mngr_->addSystem<RenderSystem>();
    // MoruloBlestFighterystem_ = mngr_->addSystem<MoruloBlestFighterSystem>();
    // bulletSystem_ = mngr_->addSystem<BulletsSystem>();
    // fighterSystem_ = mngr_->addSystem<FighterSystem>();
    // fighterGunSystem = mngr_->addSystem<FighterGunSystem>();
    // collisionSystem_ = mngr_->addSystem<CollisionSystem>();
    // gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();

    textureManager->init();
    fontManager->init();
}

void MoruloBlestFighter::closeGame()
{
    //  delete mngr_;
    // mngr_ = nullptr;
}

void MoruloBlestFighter::start()
{
    exit_ = false;
    auto ih = InputHandler::instance();
    while (!exit_)
    {
        Uint32 startTime = game_->getTime();
        SDL_SetRenderDrawColor(game_->getRenderer(), 255, 0, 0, 0);
        SDL_RenderClear(game_->getRenderer());

        ih->update();
        if (ih->keyDownEvent())
        {
            if (ih->isKeyDown(SDLK_ESCAPE))
            {
                exit_ = true;
                break;
            }
        }

        // mngr_->refresh();

        // gameCtrlSystem_->update();
        // ghostsSystem_->update();
        // pacmanSystem_->update();
        // foodSystem_->update();
        // collisionSystem_->update();
        // renderSystem_->update();
        // //Audio sistem implementado
        // audioSystem_->update();

        // this is needed for sending the messages!
        // mngr_->flushMessages();

        SDL_RenderPresent(game_->getRenderer());

        Uint32 frameTime = game_->getTime() - startTime;
        if (frameTime < 10)
            SDL_Delay(10 - frameTime);
    }
}