/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 06:09:20 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 09:15:53 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#define MAX_TEXTURE_RES 4096
#define GLM_ENABLE_EXPERIMENTAL
#define GLEW_STATIC

// #include <OpenGL/gl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <algorithm>
#include <bitset>
#include <ctime>
#include <random>
#include <cstddef>
#include <sstream>
// #include <stdio.h>
// #include <cstdio>

#define LEFT	            1
#define RIGHT	            2
#define UP		            4
#define DOWN	            8

#define SOFT_BRICK_LEFT		1
#define SOFT_BRICK_RIGHT	2
#define SOFT_BRICK_UP		4
#define SOFT_BRICK_DOWN		8
#define HARD_BRICK_LEFT		16
#define HARD_BRICK_RIGHT	32
#define HARD_BRICK_UP		64
#define HARD_BRICK_DOWN		128


const float                 AGENT_WIDTH = 64;
const float                 AGENT_RADIUS = AGENT_WIDTH / 2.0f;

const int                   TILE_WIDTH = 64;
const float                 TILE_RADIUS = (float)TILE_WIDTH / 2.0f;

const int                   BOMB_RADIUS = 64;
const float                 MIN_BOMB_COLLISION_DISTANCE = AGENT_RADIUS + (BOMB_RADIUS * 2);
const float                 MIN_CIRCULAR_COLLISION_DISTANCE = (AGENT_RADIUS) * 2.0f;
const float                 MIN_AABB_COLLIDE_DISTANCE = AGENT_RADIUS + TILE_RADIUS - 5;

const char                  DOT = '.';
const char                  SOFT_BRICK = 'G';
const char                  HARD_BRICK = 'R';
const char                  SIDE_HARD_BRICK = 'L';

const int                   MAX_BOMB = 6;
const int                   ZERO = 0;

const int                   BULLET_RADIUS = 5;
const int                   ZERO_N = 0;

const float                 HUMAN_SPEED = 1.0f;
const float                 ZOMBIE_SPEED = 1.3f;
const float                 PLAYER_SPEED = 5.0f;

const float                 DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int                   MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float                 MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float                 DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float                 MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime



enum eBombState {
	waitingForExplosion,
	exploding,
	exploded
};

enum eGameState {
	WON,
	G_DEAD,
	G_EXIT
};

enum eBrickType {
	SOFT,
	HARD,
	eDOT
};

enum class GameState {
	PLAY,
	EXIT
};

enum class DIR {
	EMPTY,
	LEFT_C,
	RIGHT_C,
	UP_C,
	DOWN_C
};

enum ePlayerState {
	P_ALIVE,
	P_DEAD
};

enum eZombieState {
	ALIVE,
	DEAD
};

enum eZombies {
	LEVEL_0 = 14,
	LEVEL_1 = 42,
	LEVEL_2 = 70,
	LEVEL_3 = 7,
	LEVEL_4 = 35,
	LEVEL_5 = 7,
	LEVEL_6 = 0,
	LEVEL_7 = 28,
};

#endif