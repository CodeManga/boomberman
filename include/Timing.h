/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:42:07 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:42:07 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
#define TIMING_H

#include "Includes.h"

namespace Gameengine {

	///Calculates FPS and also limits FPS
	class FpsLimiter {
	public:
		FpsLimiter();

		// Initializes the FPS limiter. For now, this is
		// analogous to setMaxFPS
		void init(float maxFPS);

		// Sets the desired max FPS
		void setMaxFPS(float maxFPS);

		void begin();

		// end() will return the current FPS as a float
		float end();
	private:
		// Calculates the current FPS
		void calculateFPS();

		// Variables
		float _fps;
		float _maxFPS;
		float _frameTime;
		unsigned int _startTicks;
	};


}

#endif 