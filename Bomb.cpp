/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bomb.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:02 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:02 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bomb.h"

Bomb::Bomb(glm::vec2 pos, Gameengine::SoundEffect explosionSoundEffec) :
	m_position(pos), 
	m_maxBombPerCircle(1), 
	m_bombState(eBombState::waitingForExplosion),
	m_frameCounter(0.0f),
	m_explosionSoundEffec(explosionSoundEffec),
	m_state(0)
{

}


Bomb::~Bomb()
{
}

glm::vec2 Bomb::getPosition() const 
{ 
	return m_position; 
}

bool Bomb::update(std::vector<Level*> levels, int currentLevel, float deltaTime)
{
	if (m_bombState == eBombState::exploding || m_bombState == eBombState::waitingForExplosion) {
		m_frameCounter += 1.0f * deltaTime;
	}
	if (m_frameCounter > 150.0f) {
		if (m_frameCounter < 160.0f) {
			m_explosionSoundEffec.play();
		}
		m_bombState = eBombState::exploding;
	}
	if (m_frameCounter > 200.0f) {
		m_bombState = eBombState::exploded;
		m_frameCounter = 0.0f;
	}
	m_deltaTime = deltaTime;

	unsigned int state = collideWithWorld(levels[currentLevel]->getLevelData());
	if (state & SOFT_BRICK_DOWN) {
		//std::cout << "Soft Brick down" << std::endl;
		//return true;
	} 
	if (state & SOFT_BRICK_UP) {
		//std::cout << "Soft Brick up" << std::endl;
		//return true;
	}
	if (state & SOFT_BRICK_LEFT) {
		//std::cout << "Soft Brick left" << std::endl;
		//return true;
	}
	if (state & SOFT_BRICK_RIGHT) {
		//std::cout << "Soft Brick right" << std::endl;
		//return true;
	}
	/*else if (collideWithWorld(levels[currentLevel]->getLevelData()) == eBrickType::SOFT) {
		std::cout << "soft brick" << std::endl;
		return true;
	} else if (collideWithWorld(levels[currentLevel]->getLevelData()) == eBrickType::eDOT) {
		std::cout << "Dot" << std::endl;
		return true;
	}*/


	return true;

}

bool Bomb::collideWithAgent(const glm::vec2& agentPosition) {

	glm::vec2 centerPosA = m_position;
	glm::vec2 centerPosB = agentPosition + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_BOMB_COLLISION_DISTANCE - distance;
	if (collisionDepth > 0) {
		return true;
	}
	return false;
}

unsigned int Bomb::collideWithWorld(const std::vector<std::string>& levelData) {
	glm::ivec2 gridPosition;
	gridPosition.x = static_cast<int>(floor(m_position.x / (float)TILE_WIDTH));
	gridPosition.y = static_cast<int>(floor(m_position.y / (float)TILE_WIDTH));

	// If we are outside the world, just return

	if (gridPosition.x < (int)ZERO || gridPosition.x >= (int)levelData[0].size() ||
		gridPosition.y < (int)ZERO || gridPosition.y >= (int)levelData.size()) {
		return eBrickType::HARD;
	}

	m_state = 0;
	if (m_bombState == eBombState::exploding) {
		if (levelData[gridPosition.y][gridPosition.x + 1] == SOFT_BRICK) {
			// Right soft brick
			/*std::cout << "right: " << levelData[gridPosition.y][gridPosition.x + 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x + 1 << std::endl;
*/
			m_state |= SOFT_BRICK_RIGHT;
		}
		if (levelData[gridPosition.y][gridPosition.x - 1] == SOFT_BRICK) {
			// Left soft brick
			/*std::cout << "left: " << levelData[gridPosition.y][gridPosition.x - 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x - 1 << std::endl;
*/
			m_state |= SOFT_BRICK_LEFT;
		}
		if (levelData[gridPosition.y - 1][gridPosition.x] == SOFT_BRICK) {
			// down soft brick
			/*std::cout << "down " << levelData[gridPosition.y - 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y - 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= SOFT_BRICK_DOWN;
		}
		if (levelData[gridPosition.y + 1][gridPosition.x] == SOFT_BRICK) {
			// Up soft brick
			/*std::cout << "UP " << levelData[gridPosition.y + 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y + 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= SOFT_BRICK_UP;
		}
		if (levelData[gridPosition.y][gridPosition.x + 1] == SOFT_BRICK) {
			// Right soft brick
			/*std::cout << "right: " << levelData[gridPosition.y][gridPosition.x + 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x + 1 << std::endl;
*/
			m_state |= SOFT_BRICK_RIGHT;
		}
		if (levelData[gridPosition.y][gridPosition.x - 1] == SOFT_BRICK) {
			// Left soft brick
			/*std::cout << "left: " << levelData[gridPosition.y][gridPosition.x - 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x - 1 << std::endl;
*/
			m_state |= SOFT_BRICK_LEFT;
		}
		if (levelData[gridPosition.y - 1][gridPosition.x] == SOFT_BRICK) {
			// down soft brick
			/*std::cout << "down " << levelData[gridPosition.y - 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y - 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= SOFT_BRICK_DOWN;
		}
		if (levelData[gridPosition.y + 1][gridPosition.x] == SOFT_BRICK) {
			// Up soft brick
			/*std::cout << "UP " << levelData[gridPosition.y + 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y + 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= SOFT_BRICK_UP;
		}

		if (levelData[gridPosition.y][gridPosition.x + 1] == HARD_BRICK) {
			// Right soft brick
			/*std::cout << "right: " << levelData[gridPosition.y][gridPosition.x + 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x + 1 << std::endl;
*/
			m_state |= HARD_BRICK_RIGHT;
		}
		if (levelData[gridPosition.y][gridPosition.x - 1] == HARD_BRICK) {
			// Left soft brick
			/*std::cout << "left: " << levelData[gridPosition.y][gridPosition.x - 1];
			std::cout << " Position: " << gridPosition.y << " " << gridPosition.x - 1 << std::endl;
*/
			m_state |= HARD_BRICK_LEFT;
		}
		if (levelData[gridPosition.y - 1][gridPosition.x] == HARD_BRICK) {
			// down soft brick
			/*std::cout << "down " << levelData[gridPosition.y - 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y - 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= HARD_BRICK_DOWN;
		}
		if (levelData[gridPosition.y + 1][gridPosition.x] == HARD_BRICK) {
			// Up soft brick
			/*std::cout << "UP " << levelData[gridPosition.y + 1][gridPosition.x];
			std::cout << " Position: " << gridPosition.y + 1 << " " << gridPosition.x << std::endl;
*/
			m_state |= HARD_BRICK_UP;
		}
		std::cout << "state: " << std::bitset<8>(m_state) << std::endl;
	/*	else if (levelData[gridPosition.y][gridPosition.x] == HARD_BRICK) {
			return eBrickType::HARD;
		}
		else if (levelData[gridPosition.y][gridPosition.x] == SIDE_HARD_BRICK) {
			return eBrickType::HARD;
		}*/
	}
	//std::cout << "center: " << levelData[gridPosition.y][gridPosition.x];
	//std::cout << " Position: " << gridPosition.y << " " << gridPosition.x << std::endl;
	
		return m_state;
}

void Bomb::draw(Gameengine::SpriteBatch& spriteBatch)
{
	if (getBombState() == eBombState::waitingForExplosion) {
		glm::vec4 destRect(m_position.x,
			m_position.y,
			BOMB_RADIUS,
			BOMB_RADIUS);

		Gameengine::ColorRGBA8 color = Gameengine::ColorRGBA8(255, 255, 255, 255);

		Gameengine::GLTexture texture = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/bomb_sprite1.png");
		Gameengine::TileSheet drawTexture;
		drawTexture.init(texture, glm::ivec2(4, 1));

		static int numTiles = 4;
		static int tileIndex = 0;
		static float animSpeed = 0.08f;

		if (m_animTime > 1.0f) {
			m_animTime = 0.4f;
		}

		m_animTime += animSpeed * m_deltaTime;

		tileIndex = tileIndex + static_cast<int>(m_animTime) % numTiles;
		//std::cout << "tileIndex: " << tileIndex << std::endl;
		//std::cout << "animTime: " << m_animTime << std::endl;
		//std::cout << "deltaTime: " << m_deltaTime << std::endl;

		spriteBatch.draw(destRect, drawTexture.getUVs(tileIndex), drawTexture.texture.id, 0.0f, color);
	}
	else if (getBombState() == eBombState::exploding)
	{
		glm::vec4 destRect(m_position.x,
			m_position.y,
			BOMB_RADIUS,
			BOMB_RADIUS);

		Gameengine::ColorRGBA8 color = Gameengine::ColorRGBA8(255, 255, 255, 255);

		Gameengine::GLTexture texture = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/explosion2.png");
		Gameengine::TileSheet drawTexture;
		//                               (collomn, row)
		drawTexture.init(texture, glm::ivec2(2, 1));

		spriteBatch.draw(destRect, drawTexture.getUVs(1), drawTexture.texture.id, 0.0f, color); // core
		if (m_state & SOFT_BRICK_DOWN || m_state & HARD_BRICK_DOWN) {
			
		}
		else {
			glm::vec4 destRect1(m_position.x,
				m_position.y - BOMB_RADIUS,
				BOMB_RADIUS,
				BOMB_RADIUS);
			spriteBatch.draw(destRect1, drawTexture.getUVs(0), drawTexture.texture.id, 0.0f, color); // bottom
		}
		if (m_state & SOFT_BRICK_UP || m_state & HARD_BRICK_UP) {
			
		}
		else {
			glm::vec4 destRect2(m_position.x,
				m_position.y + BOMB_RADIUS,
				BOMB_RADIUS,
				BOMB_RADIUS);
			spriteBatch.draw(destRect2, drawTexture.getUVs(0), drawTexture.texture.id, 0.0f, color); // top
		}
		if (m_state & SOFT_BRICK_LEFT || m_state & HARD_BRICK_LEFT) {
			
		}
		else {
			glm::vec4 destRect3(m_position.x - BOMB_RADIUS,
				m_position.y,
				BOMB_RADIUS,
				BOMB_RADIUS);
			spriteBatch.draw(destRect3, drawTexture.getUVs(0), drawTexture.texture.id, 0.0f, color); // left
		}
		if (m_state & SOFT_BRICK_RIGHT || m_state & HARD_BRICK_RIGHT) {
			
		}
		else {
			glm::vec4 destRect4(m_position.x + BOMB_RADIUS,
				m_position.y,
				BOMB_RADIUS,
				BOMB_RADIUS);
			spriteBatch.draw(destRect4, drawTexture.getUVs(0), drawTexture.texture.id, 0.0f, color); // right
		}
	}
	
}


void Bomb::setBombPerCircle(int increase)
{
	m_maxBombPerCircle += increase;
}

int Bomb::getBombPerCircle() const
{
	return m_maxBombPerCircle;
}

eBombState Bomb::getBombState() const
{
	return m_bombState;
}