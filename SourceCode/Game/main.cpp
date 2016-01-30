#include <string>
#include <iostream>

#include <SDL\SDL.h>

#define GLM_SWIZZLE
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <GL\glew.h>
#include <SDL\SDL_opengl.h>
#include <GL\gl.h>

#include "Window.h"
#include "Renderer.h"

#include "Mesh.h"
#include "Shader.h"


#define PROGRAM_NAME "Red Book - Chapter 3 - Draw Commands"

void Initialize();
void Display();
void Finalize(void);
void Reshape(int width, int height);

float aspect;
GLuint render_prog;
GLuint vao;
GLuint vbo;
GLuint ebo;

//Shader* currentShader;
//Mesh* triangle;

GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;

void Initialize() {

	//triangle = Mesh::GenerateTriangle();

	//render_model_matrix_loc = glGetUniformLocation(render_prog, "modelMatrix");
	//render_projection_matrix_loc = glGetUniformLocation(render_prog, "projectionMatrix");

	//// A single triangle
	//static const GLfloat vertex_positions[] = {
	//	-1.0f, -1.0f, 0.0f, 1.0f,
	//	1.0f, -1.0f, 0.0f, 1.0f,
	//	-1.0f, 1.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, 0.0f, 1.0f,
	//};

	//// Color for each vertex
	//static const GLfloat vertex_colors[] = {
	//	1.0f, 1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f, 1.0f
	//};

	//// Indices for the triangle strips
	//static const GLushort vertex_indices[] = {
	//	0, 1, 2
	//};

	//// Set up the element array buffer
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

	//// Set up the vertex attributes
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) +sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

}

void Display() {
	//glm::mat4 model_matrix;

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate simple shading program
	//glUseProgram(render_prog);

	// Set up the model and projection matrix
	//glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
	//glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	// Set up for a glDrawElements call
	/*glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);*/

	// Draw Arrays...
	//model_matrix = glm::mat4(1.0f);//glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, -5.0f));
	//glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	
	//triangle->Draw();

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	// DrawElements
	//model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -5.0f));
	//glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

	//// DrawElementsBaseVertex
	//model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -5.0f));
	//glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	//glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

	//// DrawArraysInstanced
	//model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, -5.0f));
	//glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}

void Finalize(void) {
	//glUseProgram(0);
	//glDeleteProgram(render_prog);
	//glDeleteVertexArrays(1, &vao);
	//glDeleteBuffers(1, &vbo);
}


int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	} else {
		std::cout << "General SDL system init: Success!" << std::endl;
	}

	Window w(512, 512);

	if (!w.isInitialized()) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	} else {
		std::cout << "SDL window init: Success!" << std::endl;
	}

	Renderer r(w);
	
	bool quit = false;

	//Initialize();
	SDL_Event event;
	
	while (!quit) {

		GLenum err = GL_NO_ERROR;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << err << std::endl;
		}

		r.RenderScene();
		//Display();

		w.SwapBuffers();

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				quit = true;
			}

		}

	}

	//Finalize();

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	r.~Renderer();
	w.~Window();
	SDL_Quit();

	return 0;
}