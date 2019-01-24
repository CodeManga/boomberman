/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:28 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:28 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.h"

Human::Human() /*:
	m_frames(0)*/
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos) {

	static std::mt19937 randomEngine(static_cast<unsigned int>(time(nullptr)));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	m_health = 20;
	m_color = Gameengine::ColorRGBA8(128, 255, 0, 255);

	m_speed = speed;
	m_position = pos;
	// Get random direction
	m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	m_direction = glm::vec2(1.0f, 0.0f);
	// Make sure direction isn't zero
	if (m_direction.length() == 0) {
		m_direction = glm::vec2(1.0f, 0.0f);
	}

	m_direction = glm::normalize(m_direction);

	m_textureID = Gameengine::ResourceManager::getTexture("Textures/bomberman/player1.png").id;
}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime) 
{
	(void)humans;
	(void)zombies;
	(void)levelData;
	//static std::mt19937 randomEngine(time(nullptr));
	//static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

	m_position += m_direction * m_speed * deltaTime;

	//// Randomly change direction every 20 frames
	//if (m_frames == 20) {
	//	m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	//	m_frames = 0;
	//}
	//else {
	//	m_frames++;
	//}

	//if (collideWithLevel(levelData)) {
	//	m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	//}
}

void Human::draw(Gameengine::SpriteBatch& m_spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	m_spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}