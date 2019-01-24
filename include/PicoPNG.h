/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PicoPNG.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:38:31 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:38:31 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PICOPNG_H
#define PICOPNG_H

#include "Includes.h"

namespace Gameengine {

	extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
}

#endif