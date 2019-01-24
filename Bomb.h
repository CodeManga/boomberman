/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bomb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:06 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:06 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMB_H
#define BOMB_H

// #include <glm/glm.hpp>
#include "include/Includes.h"
#include "include/SpriteBatch.h"
#include "include/AudioEngine.h"
#include "include/GLTexture.h"
#include "include/ResourceManager.h"
#include "include/TileSheet.h"

#include "Level.h"

class Humans;
class Zombie;
class Agent;


class Bomb
{
public:
	Bomb(glm::vec2 position, Gameengine::SoundEffect explosionSoundEffec);
	~Bomb();
	// When update returns true, delete bullet
	bool update(std::vector<Level*> levels, int currentLevel, float deltaTime);

	void draw(Gameengine::SpriteBatch& spriteBatch);

	bool collideWithAgent(const glm::vec2& agentPosition);

	void setBombPerCircle(int increase);

	int getBombPerCircle() const;
	eBombState getBombState() const;

	glm::vec2 getPosition() const;

private:
	
	unsigned int collideWithWorld(const std::vector<std::string>& levelData);

	glm::vec2 m_position;
	int m_maxBombPerCircle;
	float m_animTime = 0.0f;
	float m_deltaTime = 0.0f;

	// int m_currentLevel;
	std::vector<Level*> m_levels;
	eBombState m_bombState;
	float m_frameCounter;
	Gameengine::SoundEffect m_explosionSoundEffec;
	//Uint32 m_detonationTime;
	// eBrickType m_brickType;
	unsigned int m_state;
};

#endif 