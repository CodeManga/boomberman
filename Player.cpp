/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:50 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:50 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.h"


Player::Player()
{
	// Empty
}

Player::~Player() {
	// Empty
	delete m_bombManager[m_currentManager];
}

void Player::init(float speed,
				glm::vec2 pos,
				Gameengine::InputManager* inputManager,
				Gameengine::Camera2D* camera,
				std::vector<Bomb>* bombs) 
{
	Gameengine::GLTexture texture = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/player3.png");
	m_playerState = ePlayerState::P_ALIVE;
	m_speed = speed;
	m_position = pos;
	_inputManager = inputManager;
	m_bombs = bombs;
	_camera = camera;
	m_color = Gameengine::ColorRGBA8(255, 255, 255, 255);
	m_health = 150;
	m_dir = DIR::RIGHT_C;

	// Set Player Bomb Manager

	//m_textureID = Gameengine::ResourceManager::getTexture("Textures/bomberman/player1.png").id;
	m_texture.init(texture, glm::ivec2(9, 4));
	m_audioEngine.init();
}

void Player::setPlayerState(ePlayerState state)
{
	m_playerState = state;
}

ePlayerState Player::getPlayerState(void) const
{
	return m_playerState;
}

void Player::addManager(BombManager *bombManager)
{
	m_bombManager.push_back(bombManager);
	m_currentManager = 0;
}

void Player::drawPlayer(Gameengine::SpriteBatch& m_spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;


	static int numTiles = 1;
	static int tileIndex = 0;
	static float animSpeed = 0.43f;

	if (m_dir == DIR::RIGHT_C || m_previousDir == DIR::RIGHT_C) {
		if (m_dir == DIR::EMPTY) {
			numTiles = 1;
		}
		else {
			numTiles = 8;
		}
		tileIndex = 18;
	}else if (m_dir == DIR::LEFT_C || m_previousDir == DIR::LEFT_C) {
		if (m_dir == DIR::EMPTY) {
			numTiles = 1;
		}
		else {
			numTiles = 8;
		}
		tileIndex = 27;
	}else if (m_dir == DIR::UP_C || m_previousDir == DIR::UP_C) {
		if (m_dir == DIR::EMPTY) {
			numTiles = 1;
		}
		else {
			numTiles = 8;
		}
		tileIndex = 0;
	}else if (m_dir == DIR::DOWN_C || m_previousDir == DIR::DOWN_C) {
		if (m_dir == DIR::EMPTY) {
			numTiles = 1;
		}
		else {
			numTiles = 8;
		}
		tileIndex = 8;
	}
	if (m_playerState == ePlayerState::P_DEAD) {
		numTiles = 1;
		tileIndex = 1;
	}
	m_animTime += animSpeed * m_deltaTime;

	tileIndex = tileIndex + static_cast<int>(m_animTime) % numTiles;

	m_spriteBatch.draw(destRect, 
				m_texture.getUVs(tileIndex), 
				m_texture.texture.id, 
				0.0f, 
				m_color, 
				m_direction);
}

void Player::update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies,
					float deltaTime) 
{
	m_deltaTime = deltaTime;
	m_previousDir = m_dir;
	m_dir = DIR::EMPTY;
	(void)humans;
	(void)zombies;

	if (_inputManager->isKeyDown(SDLK_w)) {
		
		/*Gameengine::SoundEffect up = m_audioEngine.loadSoundEffect("Sound/up-down.ogg");
		up.play();*/
		m_position.y += m_speed * deltaTime;
		m_dir = DIR::UP_C;
	}
	else if (_inputManager->isKeyDown(SDLK_s)) {
		/*Gameengine::SoundEffect down = m_audioEngine.loadSoundEffect("Sound/up-down.ogg");
		down.play();*/
		m_position.y -= m_speed * deltaTime;
		m_dir = DIR::DOWN_C;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
	/*	Gameengine::SoundEffect left = m_audioEngine.loadSoundEffect("Sound/left-right.ogg");
		left.play();*/
		m_position.x -= m_speed * deltaTime;
		m_dir = DIR::LEFT_C;
	}
	else if (_inputManager->isKeyDown(SDLK_d)) {
		/*Gameengine::SoundEffect right = m_audioEngine.loadSoundEffect("Sound/left-right.ogg");
		right.play();*/
		m_position.x += m_speed * deltaTime;
		m_dir = DIR::RIGHT_C;
	}

	/*if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0) {
		_currentGunIndex = 0;
	}
	else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1) {
		_currentGunIndex = 1;
	}
	else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2) {
		_currentGunIndex = 2;
	}*/

	// Plant a bomb
	m_bombManager[m_currentManager]->update(_inputManager->isKeyPressed(SDLK_SPACE), getPosition() ,*m_bombs, deltaTime);


	// glm::vec2 centerPosition = m_position + glm::vec2(AGENT_RADIUS);

	if (collideWithLevel(levelData)) {
		//wallCollision.play(0);
	}
}



//BombState Player::getState() const
//{
//	return m_bombManager.getBombState();
//}


