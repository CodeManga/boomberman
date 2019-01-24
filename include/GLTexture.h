/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLTexture.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:35:27 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:35:27 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "Includes.h"

namespace Gameengine {

    struct GLTexture {
        //std::string filePath = "";
        GLuint id;
        int width;
        int height;
    };
}

#endif 