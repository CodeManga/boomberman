/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 05:04:51 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 05:04:51 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Level_H
#define LEVEL_H

#include "include/Includes.h"
#include "include/SpriteBatch.h"
#include "include/ResourceManager.h"
#include "include/TileSheet.h"
#include "include/Error.h"

class Level
{
public:
	// Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	// Getters
	int getWidth() const { return m_levelData[0].size(); }
	int getHeight() const { return m_levelData.size(); }
	int getNumHumans() const { return m_numHumans; }
	const std::vector<std::string>& getLevelData() const { return m_levelData; }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPositions; }

	std::vector<glm::vec2> levelPoints;


private:
	std::vector<std::string> m_levelData;
	int m_numHumans;
	Gameengine::SpriteBatch m_spriteBatch;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombieStartPositions;
};

#endif