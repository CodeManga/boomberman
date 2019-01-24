#include "../include/GLSLPrograme.h"

namespace Gameengine {
	// The : _numAttributes(0) ect. is an initialization list.
	// It is a better way to initialize variables, since it avoids an extra copy. 
	GLSLPrograme::GLSLPrograme(void) :
		_numAttributes(0),
		_programeID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0)
	{

	}

	GLSLPrograme::~GLSLPrograme(void)
	{

	}


	void GLSLPrograme::compileShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
	{
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.
		//Get a program object.
		_programeID = glCreateProgram();

		//Create the vertex shader object, and store its ID
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {
			fatalError("Vertex shader failed to be created!");
		}

		//Create the fragment shader object, and store its ID
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			fatalError("Fragment shader failed to be created!");
		}

		//Compile each shader
		compileShader(vertexShaderPath, _vertexShaderID);
		compileShader(fragmentShaderPath, _fragmentShaderID);

	}

	void GLSLPrograme::linkShaders(void)
	{
		// Attach our shaders to our program
		glAttachShader(_programeID, _vertexShaderID);
		glAttachShader(_programeID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programeID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programeID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programeID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programeID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programeID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link");
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programeID, _vertexShaderID);
		glDetachShader(_programeID, _fragmentShaderID);
		// And delete shader after a successful link
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	// Adds an attribute to our shader. And should be called between compiling and linking.
	void GLSLPrograme::addAttributes(const std::string &attributeName)
	{
		glBindAttribLocation(_programeID, _numAttributes++, attributeName.c_str());
	}

	GLint GLSLPrograme::getUniformLocation(const std::string & uniformName)
	{
		GLint location = glGetUniformLocation(_programeID, uniformName.c_str());
		if (location == (GLint)GL_INVALID_INDEX) {
			fatalError("Uniform " + uniformName + " not found in shader!");
		}
		return (location);
	}

	// Enable the shader and all its attributes
	void GLSLPrograme::use(void)
	{
		glUseProgram(_programeID);
		// enable all the attributes we added with addAttribut
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	// Disable the shader
	void GLSLPrograme::unuse(void)
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	// compiles a single shader file
	void GLSLPrograme::compileShader(std::string filePath, GLuint id)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programeID = glCreateProgram();

		std::ifstream shaderFile(filePath);
		if (shaderFile.fail()) {
			perror(filePath.c_str());
			fatalError(("Failed to open " + filePath));
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line)) {
			fileContents += line + "\n";
		}

		shaderFile.close();

		// tell opengl that we want to use fileContents as the contents of the shader file
		const char *contentPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentPtr, nullptr);

		//compile the shader
		glCompileShader(id);

		//check for errors
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");
		}

	}
}