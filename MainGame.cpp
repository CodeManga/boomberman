/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainGame.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:39 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:39 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainGame.h"
#include <cstdio>


// #include <CEGUI/CEGUI.h>
// #include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

MainGame::MainGame() :
	m_screenWidth(1600),
	m_screenHeight(900),
	m_fps(0),
	m_player(nullptr),
	m_numHumansKilled(0),
	m_numZombiesKilled(0),
	m_gameState(GameState::PLAY),
	m_timer(200),
	m_rotate(1)
{
	// Empty

}

MainGame::~MainGame()
{
	// Don't forget to delete the levels!
	for (size_t i = 0; i < m_levels.size(); i++) {
		delete m_levels[i];
	}
	// Don't forget to delete the humans and zombies!
	for (size_t i = 0; i < m_humans.size(); i++) {
		delete m_humans[i];
	}
	for (size_t i = 0; i < m_zombies.size(); i++) {
		delete m_zombies[i];
	}
}

eGameState MainGame::run()
{
	initSystems();

	initLevel();

	m_music = m_audioEngine.loadMusic("Sound/stage-main-theme.ogg");
	m_music1 = m_audioEngine.loadMusic("Sound/stage-main-theme-find-the-door.ogg");

	//m_player->wallCollision = m_audioEngine.loadSoundEffect("Sound/wall.ogg");
	m_dieSoundEffect = m_audioEngine.loadSoundEffect("Sound/level_start.ogg");
	m_dieSoundEffect1 = m_audioEngine.loadSoundEffect("Sound/die.ogg");
	m_dieSoundEffect.play();
	SDL_Delay(3000);
	m_dieSoundEffect = m_audioEngine.loadSoundEffect("Sound/game-over.ogg");

	
	m_music.play(-1);

	gameLoop();
	if(m_gameState == GameState::EXIT){
		return eGameState::G_EXIT;
	}
	return eGameState::G_EXIT;
}

void MainGame::initSystems()
{
	// Initialize the game engine
	Gameengine::init();

	// Initialize sound, must happen after Gameengine::init
	m_audioEngine.init();

	// Create our window
	m_window.create("Bomberman", m_screenWidth, m_screenHeight, 0);

	// Grey background color
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// Set up the shaders
	initShaders();

	// Initialize our spritebatch
	m_agentSpriteBatch.init();
	m_hudSpriteBatch.init();

	// Initialize sprite font
	m_spriteFont = new Gameengine::SpriteFont("Fonts/chintzy.ttf", 64);

	// Set up the camera
	m_camera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));

}

void MainGame::initLevel()
{
	// Level 1
	m_levels.push_back(new Level("Levels/map_b.txt"));
	m_currentLevel = 0;

	//m_levels.front()->levelPoints

	m_player = new Player();
	m_player->init(PLAYER_SPEED, m_levels[m_currentLevel]->getStartPlayerPos(), &m_inputManager, &m_camera, &m_bombs);

	m_humans.push_back(m_player);
	
	

	std::mt19937 randomEngine;
	randomEngine.seed(static_cast<unsigned int>(time(nullptr)));

	std::uniform_int_distribution<int> randX(2, m_levels[m_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, m_levels[m_currentLevel]->getHeight() - 2);

	// Add the zombies
	const std::vector<glm::vec2>& zombiePositions = m_levels[m_currentLevel]->getZombieStartPositions();
	for (size_t i = 0; i < zombiePositions.size(); i++) {
		m_zombies.push_back(new Zombie);
		if (i < 2) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_0);
		}else if (i < 4) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_1);
		}else if (i < 6) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_2);
		}else if (i < 8) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_3);
		}else if (i < 10) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_4);
		}else if (i < 12) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_5);
		}else if (i < 14) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_6);
		}else if (i < 16) {
			m_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], eZombies::LEVEL_7);
		}
	}
	
	m_player->addManager(new BombManager(m_audioEngine.loadSoundEffect("Sound/put-bomb.ogg"), m_audioEngine.loadSoundEffect("Sound/boom.ogg")));

	}

void MainGame::initShaders()
{
	// Compile our color shader
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttributes("vertexPosition");
	m_textureProgram.addAttributes("vertexColor");
	m_textureProgram.addAttributes("vertexUV");
	m_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
	// Some helpful constants.
	

	// Used to cap the FPS
	Gameengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);

	// Zoom out the camera by 4x
	m_camera.setScale(m_zoom);
	
	// seet the rotation of the camera to normal view
	m_camera.setRotate(m_rotate);

	// Start our previousTicks variable
	Uint32 previousTicks = SDL_GetTicks();

	// Main loop
	while (m_gameState == GameState::PLAY) {
		fpsLimiter.begin();
		if (m_timer == 100) {
			m_music.pause();
			//SDL_Delay(100);
			m_dieSoundEffect1.play();
			m_music1.play(-1);
		}
		// Calculate the frameTime in milliseconds
		Uint32 newTicks = SDL_GetTicks();
		Uint32 frameTime = newTicks - previousTicks;
		previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
		// Get the total delta time
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		checkVictory();

		m_inputManager.update();

		// TODO	>> ability to move the camera
		//		>> limit the camera field of view to the game field
		//
		// Zoom in or out the camera
		if (m_inputManager.isKeyDown(SDLK_DOWN)) {
			if (m_zoom > 0.2f) {
				m_zoom -= 0.001f;
				m_camera.setScale(m_zoom);
			}
		}
		if (m_inputManager.isKeyDown(SDLK_UP)) {
			if (m_zoom < 1.0f) {
				m_zoom += 0.001f;
				m_camera.setScale(m_zoom);
			}
		}

		// Rotate the camera
		if (m_inputManager.isKeyDown(SDLK_LEFT)) {
			if (m_rotate > 1.0f) {
				m_rotate -= 1.0f;
				m_camera.setScale(m_rotate);
			}
		}
		if (m_inputManager.isKeyDown(SDLK_RIGHT)) {
			if (m_rotate < 360.0f) {
				m_rotate += 1.0f;
				m_camera.setScale(m_rotate);
			}
		}

		processInput();

		int i = 0; // This counter makes sure we don't spiral to death!
		// Loop while we still have steps to process.
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
			// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
			float deltaTime = ((totalDeltaTime < MAX_DELTA_TIME) ? totalDeltaTime : MAX_DELTA_TIME);
				//std::min(totalDeltaTime, MAX_DELTA_TIME);
			// Update all physics here and pass in deltaTime
			updateAgents(deltaTime);
			// updateBullets(deltaTime);
			updateBombs(deltaTime);
			// m_particleEngine.update(deltaTime);
			// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
			totalDeltaTime -= deltaTime;
			// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
			i++;
		}

		// Make sure the camera is bound to the player position
		m_camera.setPosition(m_player->getPosition());
		m_camera.update(m_player->getDir());
		m_hudCamera.update(m_player->getDir());

		drawGame();

		// End the frame, limit the FPS, and get the current FPS.
		m_fps = fpsLimiter.end();
		//std::cout << m_fps << std::endl;
	}
}

void MainGame::updateAgents(float deltaTime)
{
	// Update all humans
	for (size_t i = 0; i < m_humans.size(); i++) {
		m_humans[i]->update(m_levels[m_currentLevel]->getLevelData(),
			m_humans,
			m_zombies,
			deltaTime);
	}

	// Update all zombies
	for (size_t i = 0; i < m_zombies.size(); i++) {
		m_zombies[i]->update(m_levels[m_currentLevel]->getLevelData(),
			m_humans,
			m_zombies,
			deltaTime);
	}

	// Update Zombie collisions
	for (size_t i = 0; i < m_zombies.size(); i++) {
		// Collide with other zombies
		for (size_t j = i + 1; j < m_zombies.size(); j++) {
			m_zombies[i]->collideWithAgent(m_zombies[j]);
		}


		// Collide with player
		if (m_zombies[i]->collideWithAgent(m_player)) {
			m_music.stop();
			m_dieSoundEffect.play(0);
			SDL_Delay(1800);
			printf("********* You die *********\n");
			Gameengine::fatalError("DIE");
			// SDL_Quit();
			// m_gameState = GameState::EXIT;
			// m_audioEngine.destroy();
			// printf("********* You die 2 *********\n");
			exit(69);
			//Gameengine::fatalError("YOU LOSE");
			// ToDo 
			// Make the game exit to a main menu
		}
	}

	// Update Human collisions
	for (size_t i = 0; i < m_humans.size(); i++) {
		// Collide with other humans
		for (size_t j = i + 1; j < m_humans.size(); j++) {
			m_humans[i]->collideWithAgent(m_humans[j]);
		}
	}
	// dont forget to update zombies
	for (size_t i = 0; i < m_levels.front()->levelPoints.size(); i++) {

	}
}

void MainGame::updateBombs(float deltaTime)
{
	for (size_t i = 0; i < m_bombs.size(); i++) {
		m_bombs[i].update(m_levels, m_currentLevel, deltaTime);
	}

	// bool wasBulletRemoved;

	// Collide with humans and zombies
	for (size_t i = 0; i < m_bombs.size(); i++) {
		// wasBulletRemoved = false;
		// Loop through zombies
		for (size_t j = 0; j < m_zombies.size(); ) {
			// Check collision
			if (m_bombs[i].collideWithAgent(m_zombies[j]->getPosition())) {
				// Add blood
				//addBlood(m_bullets[i].getPosition(), 5);
				if (m_bombs[i].getBombState() == eBombState::exploding) {
					// Damage zombie, and kill it if its out of health
					m_zombies[j]->setZombieState(eZombieState::DEAD);
					// If the zombie died, remove him
					//drawDeadZombie();
					delete m_zombies[j];
					m_zombies[j] = m_zombies.back();
					m_zombies.pop_back();
					m_numZombiesKilled++;
					break;
				}
				else {
					j++;
				}
			}
			else {
				j++;
			}
		}
	}
}

void MainGame::checkVictory() {
	// TODO: Support for multiple levels!
	// _currentLevel++; initLevel(...);

	// If all zombies are dead we win!
	if (m_zombies.empty() || !m_timer) {
		// Print victory message level-complete.ogg
		Gameengine::SoundEffect levelComplete = m_audioEngine.loadSoundEffect("Sound/level-complete.ogg");
		m_music.stop();
		SDL_Delay(1000);
		levelComplete.play();
		SDL_Delay(3000);
		std::printf("*** You win! ***\n You killed %d humans and %d zombies. There are %d/%d civilians remaining",
			m_numHumansKilled, m_numZombiesKilled, (int)m_humans.size(), m_levels[m_currentLevel]->getNumHumans());

		// Easy way to end the game :P
		Gameengine::fatalError(""); 
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(static_cast<float>(evnt.motion.x), static_cast<float>(evnt.motion.y));
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
	if (m_inputManager.isKeyPressed(SDLK_ESCAPE)) {
		m_gameState = GameState::EXIT;
	}
}
 

void MainGame::drawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use();

	// Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	m_levels[m_currentLevel]->draw();

	// Begin drawing agents
	m_agentSpriteBatch.begin();

	const glm::vec2 agentDims(AGENT_RADIUS * 2.0f);


	// draw the player
	m_player->drawPlayer(m_agentSpriteBatch);

	// Draw the zombies
	for (size_t i = 0; i < m_zombies.size(); i++) {
		if (m_camera.isBoxInView(m_zombies[i]->getPosition(), agentDims)) {
			//std::cout << "Zombie: " << i << " " <<  m_zombies[i]->getIndex() << std::endl;
			m_zombies[i]->draw(m_agentSpriteBatch);
		}
	}

	// Draw the bombs
	for (size_t i = 0; i < m_bombs.size(); i++) {
			m_bombs[i].draw(m_agentSpriteBatch);
		
	}

	// End spritebatch creation
	m_agentSpriteBatch.end();

	// Render to the screen
	m_agentSpriteBatch.renderBatch();

	// Render the heads up display
	drawHud();

	// Unbind the program
	m_textureProgram.unuse();

	// Swap our buffer and draw everything to the screen!
	m_window.swapBuffer();
}

void MainGame::drawHud() {
	char buffer[256];
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;

	std::string str1;
	std::string str2;
	std::string str3;
	buffer[0] = '\0';


	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_hudSpriteBatch.begin();

	ss1 << "Num Humans ";
	ss1 <<  m_humans.size();
	str1 = ss1.str();
	m_spriteFont->draw(m_hudSpriteBatch, str1.c_str(), glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, Gameengine::ColorRGBA8(255, 255, 255, 255));

	ss2 << "Num Enemies ";
	ss2 <<  m_zombies.size();
	str2 = ss2.str();
	m_spriteFont->draw(m_hudSpriteBatch, str2.c_str(), glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, Gameengine::ColorRGBA8(255, 255, 255, 255));
	
	

	ss3 << "Time ";
	ss3 <<  m_timer;
	str3 = ss3.str();
	 
	static int timer = 0;
	if (timer % 200 == 0) {
		m_timer--;
	}
	timer++;
	m_spriteFont->draw(m_hudSpriteBatch, str3.c_str(), glm::vec2(0, 72),
		glm::vec2(0.5), 0.0f, Gameengine::ColorRGBA8(255, 255, 255, 255));

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}