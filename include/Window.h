/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:42:45 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:42:45 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
#define WINDOW_H

#include "Includes.h"
#include "Error.h"

namespace Gameengine {
	enum WindowFlags {
		INVISIBLE = 	0x1,
		FULLSCREEN = 	0x2,
		BOARDERLESS = 	0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer(void);

		int getScreenWidth(void);
		int getScreenHeight(void);

	private:
		SDL_Window *_sdlWindow;
		int _screenWidth;
		int _screenHeight;
	};
}

#endif 