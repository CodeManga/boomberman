#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include "Bomberman.hpp"

enum GameMode
{
	MAINMENU,
	GAMEPLAY,
	GAMEPAUSE,
	SETTINGS,
	PAUSE,
	SCREEN,
	KEYS,
};

class Graphics
{
public:
	Graphics();
	~Graphics();
	void setDrawMode(GameMode mode);
    GameMode getDrawMode();

private:
	GameMode drawMode;
};

#endif
