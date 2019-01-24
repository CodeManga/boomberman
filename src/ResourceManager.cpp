#include "../include/ResourceManager.h"

namespace Gameengine {

	// Always rember to initialize static variables
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath) 
	{
		return _textureCache.getTexture(texturePath);
	}

}