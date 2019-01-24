#include "BombManager.h"



BombManager::BombManager(Gameengine::SoundEffect placebombSoundEffect, Gameengine::SoundEffect explosionSoundEffec) : 
	m_placebombSoundEffect(placebombSoundEffect),
	m_explosionSoundEffect(explosionSoundEffec)
{
}


BombManager::~BombManager()
{
}

void BombManager::update(bool isKeyPressed, 
						const glm::vec2& position, 
						std::vector<Bomb>& bombs, 
						float deltaTime)
{
	if (isKeyPressed) {
		plantBomb(bombs, position);
	}
}


void BombManager::plantBomb(std::vector<Bomb>& bombs, const glm::vec2& position)
{
	m_placebombSoundEffect.play(0);
	bombs.emplace_back(position, m_explosionSoundEffect);
}

