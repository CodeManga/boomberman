/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TileSheet.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:41:45 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:41:45 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILESHEET_H
#define TILESHEET_H

#include "GLTexture.h"
#include "Includes.h"

namespace Gameengine {
	class TileSheet {
	public:
		void init(const GLTexture& texture, const glm::ivec2& tileDims) 
		{
			this->texture = texture;
			this->dims = tileDims;
		}

		glm::vec4 getUVs(int index) 
		{
			int xTile = index % dims.x;
			int yTile = index / dims.x;

			glm::vec4 uvs;
			uvs.x = xTile / (float)dims.x;
			uvs.y = yTile / (float)dims.y;
			uvs.z = 1.0f / dims.x;
			uvs.w = 1.0f / dims.y;

			return uvs;
		}

		GLTexture texture;
		glm::ivec2 dims;
	};

}

#endif 