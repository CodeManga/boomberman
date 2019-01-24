/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera2D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:34:27 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:34:27 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "Includes.h"

namespace Gameengine {

	//Camera class for 2D games
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		//sets up the orthographic matrix and screen dimensions
		void init(int screenWidth, int screenHeight);

		//updates the camera matrix if needed
		void update(const glm::vec2& pos);
		//updates the camera matrix if needed
        void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		void offsetPosition(const glm::vec2& offset) { m_position += offset; _needsMatrixUpdate = true; }
		void offsetScale(float offset) { _scale += offset; if (_scale < 0.001f) _scale = 0.001f; _needsMatrixUpdate = true; }

		//setters
		void setPosition(const glm::vec2& newPosition) { m_position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

		//getters
		const glm::vec2& getPosition() const { return m_position; }
		float getScale() const { return _scale; }
		const glm::mat4& getCameraMatrix() const { return _cameraMatrix; }
		float getAspectRatio() const { return (float)_screenWidth / (float)_screenHeight; }

		void setRotate(float rotate);

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 m_position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float m_rotate;
	};

}

#endif 