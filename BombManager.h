/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BombManager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 05:03:52 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 05:03:52 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMBMANAGER_H
#define BOMBMANAGER_H

#include "include/AudioEngine.h"

// #include "Player.h"
// #include "Level.h"
#include <vector>
#include "Bomb.h"

class BombManager
{
public:
	BombManager(Gameengine::SoundEffect placebombSoundEffect, Gameengine::SoundEffect explosionSoundEffect);
	~BombManager();

	void plantBomb(std::vector<Bomb>& bombs, const glm::vec2& position);

	void update(bool isKeyPressed, 
				const glm::vec2& position, 
				std::vector<Bomb>& bombs, 
				float deltaTime);


private:
	std::vector<std::string> m_levelData;
	Gameengine::SoundEffect m_placebombSoundEffect;
	Gameengine::SoundEffect m_explosionSoundEffect;
};

#endif