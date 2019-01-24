/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:35 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:35 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Level.h"

Level::Level(const std::string& fileName) {

	std::ifstream file;
	file.open(fileName);

	// Error checking
	if (file.fail()) {
		Gameengine::fatalError("Failed to open " + fileName);
	}

	// Throw away the first string in tmp
	std::string tmp;

	file >> tmp >> m_numHumans;

	std::getline(file, tmp); // Throw away the rest of the first line

	// Read the level data
	while (std::getline(file, tmp)) {
		m_levelData.emplace_back(tmp);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Gameengine::ColorRGBA8 whiteColor = Gameengine::ColorRGBA8(255, 255, 255, 255);

	// Render all the tiles
	int i = 0;
	for (size_t y = 0; y < m_levelData.size(); y++) {
		for (size_t x = 0; x < m_levelData[y].size(); x++) {
			// Grab the tile
			char tile = m_levelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			// Process the tile
			switch (tile) {
			case 'B':
			case 'R':
			{
				Gameengine::GLTexture texture4 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/grass.png");

				Gameengine::TileSheet drawTexture4;
				drawTexture4.init(texture4, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture4.getUVs(0),
					drawTexture4.texture.id,
					0.0f,
					whiteColor);
				Gameengine::GLTexture texture1 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/companion_cube2.png");

				Gameengine::TileSheet drawTexture1;
				drawTexture1.init(texture1, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture1.getUVs(0),
					drawTexture1.texture.id,
					0.0f,
					whiteColor);
				break;
			}
			case 'G':
			{
				Gameengine::GLTexture texture5 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/grass.png");

				Gameengine::TileSheet drawTexture5;
				drawTexture5.init(texture5, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture5.getUVs(0),
					drawTexture5.texture.id,
					0.0f,
					whiteColor);
				Gameengine::GLTexture texture = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/companion_cube_brown2.png");
				
				Gameengine::TileSheet drawTexture;
				drawTexture.init(texture, glm::ivec2(1, 1));
				
				m_spriteBatch.draw(destRect,
					drawTexture.getUVs(1),
					drawTexture.texture.id,
					0.0f,
					whiteColor);
				break;
			}
			case 'L':
				
				break;
			case '@':
			{
				Gameengine::GLTexture texture7 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/grass.png");

				Gameengine::TileSheet drawTexture7;
				drawTexture7.init(texture7, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture7.getUVs(0),
					drawTexture7.texture.id,
					0.0f,
					whiteColor);
				m_levelData[y][x] = DOT; /// So we dont collide with a @
				_startPlayerPos.x = static_cast<float>(x) * static_cast<float>(TILE_WIDTH);
				_startPlayerPos.y = static_cast<float>(y) * static_cast<float>(TILE_WIDTH);
				break;
			}
			case 'Z':
			{
				Gameengine::GLTexture texture8 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/grass.png");

				Gameengine::TileSheet drawTexture8;
				drawTexture8.init(texture8, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture8.getUVs(0),
					drawTexture8.texture.id,
					0.0f,
					whiteColor);
				m_levelData[y][x] = DOT; /// So we dont collide with a Z
				_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			}
			case DOT:
			{
				Gameengine::GLTexture texture3 = Gameengine::ResourceManager::getTexture("Textures/bomberman2/sprites/old/grass.png");

				Gameengine::TileSheet drawTexture3;
				drawTexture3.init(texture3, glm::ivec2(1, 1));

				m_spriteBatch.draw(destRect,
					drawTexture3.getUVs(0),
					drawTexture3.texture.id,
					0.0f,
					whiteColor);
				levelPoints.emplace_back(destRect.x, destRect.y);
				break;
			}
			default:
				std::printf("Unexpected symbol %c at (%zu,%zu)", tile, x, y);
				break;
				i++;
			}
		}
	}

	//int j = 0;
	////for (size_t i = 0; i < m_levelPoints.size(); i++) {
	////	std::cout << m_levelPoints[i].x << "-" << m_levelPoints[i].y << "  " << std::endl;

	////}
	//for (size_t y = 0; y < m_levelData.size(); y++) {
	//	for (size_t x = 0; x < m_levelData[y].size(); x++) {
	//		std::cout << m_levelPoints.at(j).x << "-" << m_levelPoints.at(j).y << "  ";
	//		++j;
	//	}
	//	std::cout << "" << std::endl;
	//}

	m_spriteBatch.end();

}


Level::~Level()
{
}


void Level::draw() {
	m_spriteBatch.renderBatch();
}