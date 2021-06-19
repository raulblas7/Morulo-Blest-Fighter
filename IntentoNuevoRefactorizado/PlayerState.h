#include <SDL2/SDL.h>

class PlayerState
{
public:
    PlayerState();
    ~PlayerState();

    int index;
    int xDirection;
    int yDirection;

    bool handleEvent();

    bool operator==(const PlayerState &other) const
    {
        return xDirection == other.xDirection &&
               yDirection == other.yDirection &&
               xAim == other.xAim &&
               yAim == other.yAim &&
               shooting == other.shooting;
    }
};
