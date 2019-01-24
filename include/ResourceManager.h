/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:39:26 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:39:26 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Includes.h"
#include "TextureCache.h"

namespace Gameengine {

	//This is a way for us to access all our resources, such as
	//Models or textures.
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};
}

#endif 