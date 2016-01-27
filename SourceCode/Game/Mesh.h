#pragma once

#include "MeshBuffer.h"
#include <GL/glew.h>
#include <glm.hpp>

class Mesh {

	public:

	Mesh();

	virtual ~Mesh();

	virtual void Draw();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets the texture, which will always be bound to the given texture unit.
	/// 		 The maximum number of textures is 20.</summary>
	///
	/// <param name="textureUnitIndex">Index of the texture unit to use.</param>
	/// <param name="tex">			   The texure OGL ID.</param>
	///-------------------------------------------------------------------------------------------------
	/*void SetTexture(int textureUnitIndex, GLuint tex) {
		if (textureUnitIndex >= 0 && textureUnitIndex < 20) {
			textures[textureUnitIndex] = tex;
		}
	}

	GLuint GetTexture(int textureUnitIndex) {
		return textures[textureUnitIndex];
	}*/

	static Mesh* Mesh::GenerateTriangle();

	protected:

	///-------------------------------------------------------------------------------------------------
	/// <summary>The VAO OGL object.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint vao;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The VBO. Stores the vertex attributes.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint vbo[MAX_BUFFER];

	///-------------------------------------------------------------------------------------------------
	/// <summary>Number of vertices.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint numVertices;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Copies the data to the graphics memory.</summary>
	///-------------------------------------------------------------------------------------------------
	void BufferData();

	///-------------------------------------------------------------------------------------------------
	/// <summary>The type of this mesh. Required for a the OGL draw call.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint type;

	glm::vec3* vertices;

	glm::vec4* colours;

};