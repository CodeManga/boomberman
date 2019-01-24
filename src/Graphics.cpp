#include "Graphics.hpp"

Graphics::Graphics()
{
	drawMode = MAINMENU;
}

Graphics::~Graphics() { }

void Graphics::setDrawMode(GameMode mode)
{
	drawMode = mode;
}

GameMode Graphics::getDrawMode()
{
	return drawMode;
}
