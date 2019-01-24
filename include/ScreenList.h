/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScreenList.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:39:52 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:39:52 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREENLIST_H
#define SCREENLIST_H

#include "Includes.h"
#include "IGameScreen.h"

namespace Gameengine {

	class IMainGame;
	class IGameScreen;

	class ScreenList {
	public:
		ScreenList(IMainGame* game);
		~ScreenList();

		IGameScreen* moveNext();
		IGameScreen* movePrevious();

		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);

		void destroy();

		IGameScreen* getCurrent();

	protected:
		IMainGame* m_game = nullptr;
		std::vector<IGameScreen*> m_screens;
		int m_currentScreenIndex = -1;
	};

}

#endif 