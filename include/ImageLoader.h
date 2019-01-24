/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ImageLoader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:36:12 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:36:12 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGELOADER_H
#define IMAGELOADER_H


#include "Includes.h"
#include "GLTexture.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "Error.h"

namespace Gameengine {

	//Loads images into GLTextures
	class imageLoader {
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}

#endif 