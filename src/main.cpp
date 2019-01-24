#include "shader.hpp"
#include "Graphics.hpp"
#include "Window.hpp"
#include "MainMenu.hpp"
#include "settings.hpp"

#include "screen.hpp"

GLFWwindow *window;
MainMenu *mainMenu;
Settings *settings;

Screen *screen;

Graphics *graphics;

// camera
glm::vec3 cameraPos   = glm::vec3(-1.0f, 2.0f,  2.76f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  1.0f);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{
		if (graphics->getDrawMode() == MAINMENU)
		{
			mainMenu->toggleCommands(key);
			if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
        	    glEnable(GL_DEPTH_TEST);
        }
        else if (graphics->getDrawMode() == SETTINGS)
        {
        	std::cout << "inside settings\n";
        	settings->toggleCommands(/*window,*/ key);
        }

        else if (graphics->getDrawMode() == SCREEN)
        {
        	std::cout << "inside resolutions\n";
        	screen->toggleCommands(/*window,*/ key);
        }

	}
	else if (key == GLFW_KEY_P)
	{
		graphics->setDrawMode(PAUSE);
		glEnable(GL_DEPTH_TEST);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	Sound *sound;
	int soundVal;
	bool dispVal;


    // static int    window_state = 0;//0 for fullscreen mode
	Window myWindow;
	WindowKeyEvents *keyEvents;
	// std::vector<int> removeWalls;

	myWindow.initiateSystemsWindowed();
	sound = myWindow.getSound();
	window = myWindow.getWindow();
	keyEvents = myWindow.getEvents();

	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	if (myWindow.initializeGlew() == false)
		return -1;

  //   Camera camera(cameraPos, cameraFront, cameraUp, window);
	graphics = new Graphics();


	char level_[256];
	int level_num = 1;
	sprintf(level_, " level_ : %d", level_num);

	mainMenu = new MainMenu(window, myWindow, graphics);
	mainMenu->initMenuImage();

	settings = new Settings(window, myWindow, graphics);
	settings->initSettingsImage();


	screen = new Screen(window, myWindow, graphics);
	screen->initScreenImage();
 
    mainMenu->initMenuImage();

	//======== load game state ========
	// gs.loadGameState(player, listOfWalls);
	//=================================
	//set the initial sound value
	soundVal = mainMenu->getSoundVal();
	dispVal = settings->getDispChange();
    //=========================================================================================
    //build and compile our shader program
    GLuint shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
    glUseProgram(shadersID);
    // camera.perspectiveView(shadersID);
    //====================================================================================

    do {
		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (graphics->getDrawMode())
		{
		case MAINMENU:
			sound->playMusicForvever(MUSIC_MENU1);
			mainMenu->LoadMainMenuImage();
			myWindow = mainMenu->getGameWindow();
			window = myWindow.getWindow();
			break;
		case SETTINGS:
			sound->playMusicForvever(MUSIC_MENU1);
			settings->LoadSettingsImage();
			myWindow = settings->getGameWindow();
			if (soundVal != settings->getSoundVal())
			{
				soundVal = settings->getSoundVal();
				Mix_VolumeMusic(soundVal);
			}
			if (dispVal != settings->getDispChange())
			{
				myWindow = settings->getGameWindow();
				window = myWindow.getWindow();
				keyEvents->keyEventsWrapper(window, sound, graphics);
				glfwSetKeyCallback(window, key_callback);
				shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
				std::cout << "1\n";
				dispVal = settings->getDispChange();
				std::cout << "2\n";
				glUseProgram(shadersID);
				std::cout << "3\n";

				settings->setWindow(window, myWindow, graphics);
				mainMenu->setWindow(window, myWindow, graphics);

			}
			break;
		case SCREEN:
			sound->playMusicForvever( MUSIC_MENU1);
			screen->LoadScreenImage();
			myWindow = screen->getGameWindow();
			std::cout << "Testetd" << std::endl;

			break;
		// case KEYS:
		// 	sound->playMusicForvever( MUSIC_MENU1);
		// 	// keys->LoadKeysImage();
		// 	// myWindow = keys->getGameWindow();
    
		// 	break;
		case GAMEPLAY:
			sound->playMusicForvever(MUSIC_BACK);
			sound->playMusicForvever(MUSIC_BACK);
			//------------------------------
			// camera.processKeyInput();
			glUseProgram(shadersID);
	default:
		break;
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);//

	//======================= save game state ==================
	// gs.saveGameState(*player, listOfWalls);
	//==========================================================
	// Cleanup VBO
	delete graphics;

	mainMenu->menuCleanup();
	glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
