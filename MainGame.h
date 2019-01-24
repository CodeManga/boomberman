/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainGame.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:42 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:42 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAINGAME_H
#define MAINGAME_H

#include "include/Window.h"
#include "include/InputManager.h"
#include "include/Camera2D.h"
#include "include/GLSLPrograme.h"
#include "include/SpriteBatch.h"
#include "include/SpriteFont.h"
#include "include/AudioEngine.h"
#include "include/ParticleEngine2D.h"
#include "include/ParticleBatch2D.h"
#include "include/ResourceManager.h"
#include "include/Gameengine.h"
#include "include/Error.h"
#include "include/Timing.h"
#include "include/Includes.h"

#include "MainGame.h"
// #include "Gun.h"
#include "Zombie.h"
#include "Player.h"
// #include "Bullet.h"
// #include "BombManager.h"
// #include "Bomb.h"
// #include "Level.h"

class Zombie;

class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	eGameState run();

private:
	/// Initializes the core systems
	void initSystems();

	/// Initializes the level and sets up everything
	void initLevel();

	/// Initializes the shaders
	void initShaders();

	/// Main game loop for the program
	void gameLoop();

	/// Updates all agents
	void updateAgents(float deltaTime);

	/// Updates all bullets
	// void updateBullets(float deltaTim);

	/// Updates bombs
	void updateBombs(float deltaTime);

	/// Checks the victory condition
	void checkVictory();

	/// Handles input processing
	void processInput();

	/// Renders the game
	void drawGame();

	/// Draws the HUD
	void drawHud();

	/// Adds blood to the particle engine
	// void addBlood(const glm::vec2& position, int numParticles);

	/// Member Variables
	Gameengine::Window m_window; ///< The game window

	Gameengine::GLSLPrograme m_textureProgram; ///< The shader program

	Gameengine::InputManager m_inputManager; ///< Handles input

	Gameengine::Camera2D m_camera; ///< Main Camera
	Gameengine::Camera2D m_hudCamera; ///< Hud Camera

	Gameengine::SpriteBatch m_agentSpriteBatch; ///< Draws all agents
	Gameengine::SpriteBatch m_hudSpriteBatch;

	// Gameengine::ParticleEngine2D m_particleEngine;
	// Gameengine::ParticleBatch2D* m_bloodParticleBatch;


	std::vector<Level*> m_levels; ///< vector of all levels

	int m_screenWidth = 1024;
	int m_screenHeight = 768;

	float m_fps;

	int m_currentLevel;

	Player* m_player;
	std::vector<Human*> m_humans; ///< Vector of all humans
	std::vector<Zombie*> m_zombies; ///< Vector of all zombies
	// std::vector<Bullet> m_bullets;

	int m_numHumansKilled; ///< Humans killed by player
	int m_numZombiesKilled; ///< Zombies killed by player

	Gameengine::SpriteFont* m_spriteFont;

	Gameengine::AudioEngine m_audioEngine;

	GameState m_gameState;

	float m_zoom = 0.8f;
	Gameengine::Music m_music;
	Gameengine::Music m_music1;
	Gameengine::SoundEffect m_dieSoundEffect;
	Gameengine::SoundEffect m_dieSoundEffect1;

	std::vector<Bomb> m_bombs;
	int m_timer;
	float m_rotate;
};

#endif 