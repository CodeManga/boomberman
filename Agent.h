/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Agent.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:26:55 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:26:55 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AGENT_H
#define AGENT_H

#include "include/Includes.h"
#include "include/ResourceManager.h"
#include "include/SpriteBatch.h"
#include "include/TileSheet.h"

// #include "Level.h"

// Use a for declaretion to avoid circular inclusion
class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies,
						float deltaTime) = 0;
	virtual void draw(Gameengine::SpriteBatch& m_spriteBatch);

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent* agent);


	// Return true if we died
	bool applyDamage(float damage);

	glm::vec2 getPosition() const { return m_position; }

protected:

	void checkTilePosition(const std::vector<std::string>& levelData,
		std::vector<glm::vec2>& collideTilePositions,
		float x,
		float y);

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);
	Gameengine::ColorRGBA8 m_color;
	float m_speed;
	float m_health;
	GLuint m_textureID;
	Gameengine::TileSheet m_texture;
	float m_deltaTime;
	//float m_animTime = 0.0f;

	glm::ivec2 left = glm::ivec2(0, 1);
	glm::ivec2 right = glm::ivec2(0, -1);
	glm::ivec2 up = glm::ivec2(1, 0);
	glm::ivec2 down = glm::ivec2(-1, 0);

};

#endif 