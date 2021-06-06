#include "MoruloBlestFighter.h"
#include <assert.h>
#include "SDL_macros.h"
using namespace std;

MoruloBlestFighter::MoruloBlestFighter() 
{

//game_=nullptr;
//mngr_=(nullptr);
exit_=false;
    initGame();
}

MoruloBlestFighter::~MoruloBlestFighter()
{
    closeGame();
}

void MoruloBlestFighter::initGame()
{

    //game_ = SDLGame::init("MoruloBlestFighter", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
    //SDLGame* h= new SDLGame("MoruloBlestFighter", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

    int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
    assert(sdlInit_ret == 0);
   SDL_Window* window_= SDL_CreateWindow("MoruloBlestFighter",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, _WINDOW_WIDTH_, _WINDOW_HEIGHT_, SDL_WINDOW_SHOWN);
   // assert(window_ != nullptr);
    // Create window
    
    // Create the renderer
   SDL_Renderer*renderer_=  SDL_CreateRenderer(window_, -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   // assert(renderer_ != nullptr);
    // Clear screen (background color).
    int sdlSetDrawColor_ret = SDL_SetRenderDrawColor(renderer_, 0, 100, 100,
                                                     255); // Dark grey.
    assert(sdlSetDrawColor_ret != -1);
    int sdlRenderClear_ret = SDL_RenderClear(renderer_);
    assert(sdlRenderClear_ret != -1);
    SDL_RenderPresent(renderer_);

    // hide cursor by default
    SDL_ShowCursor(0);
    /// AsteroidPool::init();
    //BulletsPool::init();

    // mngr_ = new Manager(game_);
    // renderSystem_ = mngr_->addSystem<RenderSystem>();
    // MoruloBlestFighterystem_ = mngr_->addSystem<MoruloBlestFighterSystem>();
    // bulletSystem_ = mngr_->addSystem<BulletsSystem>();
    // fighterSystem_ = mngr_->addSystem<FighterSystem>();
    // fighterGunSystem = mngr_->addSystem<FighterGunSystem>();
    // collisionSystem_ = mngr_->addSystem<CollisionSystem>();
    // gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
}

void MoruloBlestFighter::closeGame()
{
    //  delete mngr_;
    // mngr_ = nullptr;
}

void MoruloBlestFighter::start()
{
    exit_ = false;
    // auto ih = InputHandler::instance();
    while (!exit_)
    {
        Uint32 startTime = game_->getTime();
        SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x000000FF));
        SDL_RenderClear(game_->getRenderer());

        // ih->update();
        /*if (ih->keyDownEvent())
        {
            if (ih->isKeyDown(SDLK_ESCAPE))
            {
                exit_ = true;
                break;
            }
        }*/

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