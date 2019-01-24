/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:40:14 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:40:14 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"
#include "GLTexture.h"
#include "Vertex.h"
#include "ResourceManager.h"

namespace Gameengine {

	//A 2D quad that can be rendered to the screen
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);

		void draw(void);

	// private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID; // vertex buffer object ID
		GLTexture _texture;

	};
}

#endif 