/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleEngine2D.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:38:07 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:38:07 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLEENGINE2D_H
#define PARTICLEENGINE2D_H

#include "Includes.h"
#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

namespace Gameengine {

	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D {
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		// After adding a particle batch, the ParticleEngine2D becomes
		// responsible for deallocation.
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};

}

#endif 