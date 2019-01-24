/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:27:54 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:27:54 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

#include "include/InputManager.h"
#include "include/Camera2D.h"
#include "include/AudioEngine.h"
#include "include/ResourceManager.h"
#include "include/Includes.h"

#include "Human.h"
#include "Bullet.h"
#include "BombManager.h"
// #include "Bomb.h"
#include "Gun.h"

class BombManager;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed,
				glm::vec2 pos,
				Gameengine::InputManager* inputManager,
				Gameengine::Camera2D* camera,
				std::vector<Bomb>* bombs);

	void drawPlayer(Gameengine::SpriteBatch& m_spriteBatch);

	void update(const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies,
				float deltaTime) override;

	//BombState getState() const;
	Gameengine::SoundEffect wallCollision;
	void addManager(BombManager* bombManager);

	void setPlayerState(ePlayerState state);
	ePlayerState getPlayerState(void) const;
	const glm::vec2 getDir() const { return m_direction; }


private:
	Gameengine::InputManager* _inputManager;

	// int _currentGunIndex;
	float m_animTime = 0.0f;


	Gameengine::Camera2D* _camera;
	DIR m_dir;
	DIR m_previousDir;
	std::vector<BombManager*> m_bombManager;
	int m_currentManager;
	std::vector<Bomb>* m_bombs;

	ePlayerState m_playerState;
	Gameengine::AudioEngine m_audioEngine;

};

#endif 