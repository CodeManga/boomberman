/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureCache.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:41:24 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:41:24 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "Includes.h"
#include "GLTexture.h"
#include "ImageLoader.h"

namespace Gameengine {

	//This caches the textures so that multiple sprites can use the same textures
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}

#endif 