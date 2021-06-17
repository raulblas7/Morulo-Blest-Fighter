#pragma once


#include "SDLGame.h"

class MoruloBlestFighter
{

  public:
    MoruloBlestFighter();
    virtual ~MoruloBlestFighter();

    // from SDLGame
    void start();

    TexturesManager* getTextureManager()const{ return textureManager;}
    SDLGame* getGame() const { return game_;}

  private:
    void initGame();
    void closeGame();

    SDLGame* game_ = nullptr;
    TexturesManager* textureManager = nullptr;
    FontsManager* fontManager = nullptr;

    //Manager* mngr_;
    bool exit_;

    const static int _WINDOW_WIDTH_ = 640;
    const static int _WINDOW_HEIGHT_ = 480;
};