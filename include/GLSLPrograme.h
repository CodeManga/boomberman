/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLSLPrograme.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:35:07 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:35:07 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLSLPROGRAME_H
#define GLSLPROGRAME_H

#include "Includes.h"
#include "Error.h"
#include "IOManager.h"
namespace Gameengine {

	//This class handles the compilation, linking, and usage of a GLSL shader program.
	//Reference: http://www.opengl.org/wiki/Shader_Compilation
	class GLSLPrograme {
	public:
		GLSLPrograme(void);
		~GLSLPrograme(void);

		void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void linkShaders(void);

		GLint getUniformLocation(const std::string& uniformName);
		void addAttributes(const std::string& attributeName);

		void use(void);
		void unuse(void);

	private:
		int _numAttributes;
		GLuint _programeID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		// Private member functions
		void compileShader(std::string filePath, GLuint id);


	};
}

#endif 