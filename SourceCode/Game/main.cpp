#include <string>
#include <iostream>

#include "SDL.h"

#define GLM_SWIZZLE
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include "Window.h"

#include "Mesh.h"


#include "LoadShaders.h"
extern GLuint LoadShaders(ShaderInfo *shaderinfo);


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

Mesh* triangle;

GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;

void Initialize() {

	triangle = Mesh::GenerateTriangle();

	ShaderInfo shader_info[] = {
		{GL_VERTEX_SHADER, "primitive_restart.vs.glsl"},
		{GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl"},
		{GL_NONE, NULL}
	};

	render_prog = LoadShaders(shader_info);
	glUseProgram(render_prog);

	render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
	render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

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

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Display() {
	glm::mat4 model_matrix;

	// Setup
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate simple shading program
	glUseProgram(render_prog);

	// Set up the model and projection matrix
	glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	// Set up for a glDrawElements call
	/*glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);*/

	// Draw Arrays...
	model_matrix = glm::mat4(1.0f);//glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, -5.0f));
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	
	triangle->Draw();

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
	glUseProgram(0);
	glDeleteProgram(render_prog);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Reshape(int width, int height) {
	glViewport(0, 0, width, height);
	aspect = float(height) / float(width);
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

	GLenum rev;
	
	glewExperimental = GL_TRUE;
	rev = glewInit();
	
	if (GLEW_OK != rev) {
		std::cout << "GLEW init error: " << glewGetErrorString(rev) << std::endl;
		SDL_Quit();
		exit(1);
	} else {
		std::cout << "GLEW init: Success!" << std::endl;
	}

	bool quit = false;

	Initialize();
	Reshape(512, 512);
	SDL_Event event;
	
	while (!quit) {

		
		Display();
		w.SwapBuffers();

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				quit = true;
			}

		}

	}

	Finalize();

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	w.~Window();
	SDL_Quit();

	return 0;
}