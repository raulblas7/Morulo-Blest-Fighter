#pragma once

#include "Font.h"
#include <map>

/*
 *
 */
class FontsManager
{
public:
    FontsManager();
    virtual ~FontsManager();

    // supposed to be called before start using the object
    bool init();

    Font *getFont(std::size_t tag);
    bool loadFont(std::size_t tag, const string &fileName, int size);

private:
    map<int, Font *> fonts_;
    bool initialized_;
};
