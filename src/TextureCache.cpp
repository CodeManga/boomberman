#include "../include/TextureCache.h"

namespace Gameengine {

	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		// Look for the texture and see if it is in the map
		auto mitr = _textureMap.find(texturePath);

		// check if it is not in the map
		if (mitr == _textureMap.end()) {
			// Load the texture
			GLTexture newTexture = imageLoader::loadPNG(texturePath);

			// insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));

			return (newTexture);
		}

		return (mitr->second);
	}
}