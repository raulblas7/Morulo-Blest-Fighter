#pragma once

#include <map>
#include "Texture.h"
#include "Font.h"
/*
 *
 */
class TexturesManager
{
public:
    static TexturesManager instance;

	TexturesManager();
	virtual ~TexturesManager();

	// supposed to be called before start using the object
	bool init();

	Texture *getTexture(std::size_t tag)
	{
		return textures_[tag];
	}

	bool loadFromImg(std::size_t, SDL_Renderer *renderer,
					 const string &fileName);
	bool loadFromText(std::size_t, SDL_Renderer *renderer, const string &text,
					  const Font *font, const SDL_Color &color);

private:
	void storeTexture(std::size_t tag, Texture *texture);

	bool initialized_;
	map<std::size_t, Texture *> textures_;
};