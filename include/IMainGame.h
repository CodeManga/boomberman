/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMainGame.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:36:36 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:36:36 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAINGAME_H
#define IMAINGAME_H

#include "Gameengine.h"
#include "Window.h"
#include "InputManager.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"

namespace Gameengine {

	class ScreenList;
	class IGameScreen;

	class IMainGame {
	public:
		IMainGame();
		virtual ~IMainGame();

		// Runs and initializes the game
		void run();
		// Exits the game
		void exitGame();

		// Called on initialization
		virtual void onInit() = 0;
		// For adding all screens
		virtual void addScreens() = 0;
		// Called when exiting
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

		float getFps() const {
			return m_fps;
		}

		InputManager inputManager;

	protected:
		// Custom update function
		virtual void update();
		// Custom render function
		virtual void draw();

		bool init();
		bool initSystems();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		bool m_isRunning = false;
		float m_fps = 0.0f;
		Window m_window;
	};
}

#endif 