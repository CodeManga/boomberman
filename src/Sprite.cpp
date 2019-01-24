#include "../include/Sprite.h"


namespace Gameengine {

	Sprite::Sprite(void)
	{
		_vboID = 0;
		// _texture = {};
	}

	Sprite::~Sprite(void)
	{
		//Always remember to delete your buffers when
		//you are done!
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}


	//Draws the sprite to the screen
	void Sprite::draw(void)
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		// bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		// draw the 6 verteces to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable the vertac attrib array. This isn not optional.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable the vertex attrib arrays. This is not optional.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	//Initializes the sprite VBO. x, y, width, and height are
	//in the normalized device coordinate space. so, [-1, 1]
	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		//Set up our private vars
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		// generate the buffer if it has't been generated
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		//This array will hold our vertex data.
		//We need 6 vertices, and each vertex has 2
		//floats for X and Y
		Vertex vertexData[6];

		// First triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		// Second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		// initialize all the vertex colors to the same color struct
		for (int i = 0; i < 6; i++) {
			vertexData[i].setColor(255, 0, 255, 255);
		}

		vertexData[1].setColor(0, 0, 255, 255);

		vertexData[4].setColor(0, 255, 0, 255);

		//Tell opengl to bind our vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// Unbind the buffer (optional)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}