/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputManager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:37:01 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:37:01 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Includes.h"

namespace Gameengine {

	// Input manager stores a key map that maps SDL_keys to booleans.
	// If the value in the key map is true, then the key is pressed.
	// Otherwise, it is released.
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		/// Returns true if the key is held down
		bool isKeyDown(unsigned int keyID);

		/// Returns true if the key was just pressed
		bool isKeyPressed(unsigned int keyID);

		// getters
		glm::vec2 getMouseCoords() const;

	private:
		/// Returns true if the key is held down
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoords;
	};
}

#endif 