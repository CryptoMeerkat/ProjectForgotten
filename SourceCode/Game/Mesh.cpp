#include "Mesh.h"

Mesh::Mesh() {
	for (int i = 0; i < MeshBuffer::MAX_BUFFER; i++) {
		//in OGL 0 is comparable to a null pointer
		vbo[i] = 0;
	}

	//generate VAO
	glGenVertexArrays(1, &vao);
	numVertices = 0;
	vertices = NULL;
	colours = NULL;
	type = GL_TRIANGLES;

}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(MAX_BUFFER, vbo);
	delete[] vertices;
	delete[] colours;
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* m = new Mesh();
	m->numVertices = 3;

	//insert default vertices
	m->vertices = new glm::vec3[m->numVertices];
	m->vertices[0] = glm::vec3(0.0f, 0.5f, 0.0f);
	m->vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
	m->vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);

	//add colors for the vertices
	m->colours = new glm::vec4[m->numVertices];
	m->colours[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	m->BufferData();
	return m;
}

void Mesh::BufferData() {
	glBindVertexArray(vao);

	/*VERTEX BUFFER*/
	glGenBuffers(1, &vbo[VERTEX_BUFFER]);
	//next VBO operations are made o this VBO and VBO is bound to VAO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
	//copy vertices to graphics memory
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
	//defines how to the VAO interprets the VBO
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	/*COLOR BUFFER*/
	if (colours) {
		glGenBuffers(1, &vbo[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec4), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	//unbinding ensures that no one else is modifying our VAO
	glBindVertexArray(0);
}


void Mesh::Draw() {
	glBindVertexArray(vao);
	glDrawArrays(type, 0, numVertices);
	glBindVertexArray(0);
}