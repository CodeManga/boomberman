#include "../include/Gameengine.h"

namespace Gameengine {
	int init(void)
	{
		// Initializing SDL
		// SDL_Init(SDL_INIT_EVERYTHING);

		// Tell SDL that we want a double bufferd window so
		// we don't get any flickering
		// create two windows or textures to clear and draw on windows


		SDL_Init( SDL_INIT_EVERYTHING );
	    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return (0);
	}
}