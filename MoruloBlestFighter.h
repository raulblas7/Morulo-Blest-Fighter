

#include "SDLGame.h"

class MoruloBlestFighter
{

  public:
    MoruloBlestFighter();
    virtual ~MoruloBlestFighter();

    // from SDLGame
    void start();
    void stop();

  private:
    void initGame();
    void closeGame();

    SDLGame* game_;
    //Manager* mngr_;
    bool exit_;

    const static int _WINDOW_WIDTH_ = 640;
    const static int _WINDOW_HEIGHT_ = 480;
};