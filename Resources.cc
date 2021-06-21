#include "Resources.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		//{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		//{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {

		{ HelicopterTexture, "./resources/helicopter.png" },
		{ HelicopterTexture2, "./resources/helicopter2.png" },
		{ Rock, "./resources/tile.png" },
		{ Bullet, "./resources//bullet.png" },
		{ BackGround, "./resources/Fondo.png" }
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		//{ PressEnterToStartANewGame, "Press ENTER to start a new game", { COLOR(0xaaffffff) }, ARIAL16 }, //
		//{ PressEnterToContinue, "Press ENTER to continue", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		//{ GameOver, "Game Over!", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		//{ PacMan_Intro, "resources/sound/pacman_intro.wav" }, //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
	//	{ PacMan_Eat, "resources/sound/pacman_eat.wav" }, //
		//{ PacMan_Death, "resources/sound/pacman_death.wav" }, //
	//	{ PacMan_Won, "resources/sound/pacman_won.wav" }, //
};