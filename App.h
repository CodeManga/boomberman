/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 04:25:31 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 04:25:31 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
#define APP_H

#include "IMainGame.h"
#include "GameplayScreen.h"

class App : public Gameengine::IMainGame
{
public:
	App();
	~App();

	// Called on initialization
	virtual void onInit() override;
	// For adding all screens
	virtual void addScreens() override;
	// Called when exiting
	virtual void onExit() override;

private:
	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
};

#endif 