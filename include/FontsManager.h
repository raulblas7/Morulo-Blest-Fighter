#pragma once

#include "Font.h"
#include <string>
#include <map>


class FontsManager
{
public:
    FontsManager();
    virtual ~FontsManager();

    bool init();

    Font *getFont(std::size_t tag);
    bool loadFont(std::size_t tag, const std::string &fileName, int size);

private:
    map<int, Font *> fonts_;
    bool initialized_;
};