#include "../include/Window.h"

namespace Gameengine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}


	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BOARDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		// Open an SDL window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		// Set up our OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context copuld not be created!");
		}

		// Set up glew (optional but recommended)
		glewExperimental = GL_TRUE; // to prevent crushes
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}

		// Define the viewport dimensions
    	glViewport( 0, 0, screenWidth, screenHeight );
    

		// check the OpenGL version
		std::printf("***  OpenGL version: %s  ***\n", glGetString(GL_VERSION));

		// set backround color to blue
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT );

		// set VSYNC
		SDL_GL_SetSwapInterval(0);

		// enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return (0);
	}

	void Window::swapBuffer(void)
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}

	int Window::getScreenWidth(void)
	{
		return (_screenWidth);
	}

	int Window::getScreenHeight(void)
	{
		return (_screenHeight);
	}
}