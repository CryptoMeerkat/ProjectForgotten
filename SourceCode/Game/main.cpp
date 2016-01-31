#include <string>
#include <iostream>

#include <thread>
#include <chrono>

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
#include "Keyboard.h"
#include "Mouse.h"

#include "Mesh.h"
#include "Shader.h"

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

int msecLastUpdate;

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
	
	// load keyboard up
	int numKeys;
	const Uint8* keystate = SDL_GetKeyboardState(&numKeys);
	Keyboard::Instance().Initialise(keystate, numKeys);

	// load mouse up
	Mouse::Instance().Update(0);
	SDL_SetRelativeMouseMode(SDL_TRUE); // mouse is bound within window

	bool quit = false;

	SDL_Event event;
	
	//start the timer
	msecLastUpdate = SDL_Init(SDL_INIT_TIMER);

	while (!quit) {

		// first handle the user input
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				quit = true;
			}

		}

		// update the scene, AI, physics, etc.
		float deltaTime = (float) SDL_GetTicks() - msecLastUpdate;
		r.UpdateScene(deltaTime);
		msecLastUpdate = SDL_GetTicks();

		Keyboard::Instance().Update();
		Mouse::Instance().Update(deltaTime);

		if (Keyboard::Instance().GetKeyPressed(Keyboard::KEY_ESC)) {
			quit = true;
		}

		// render the scene
		r.RenderScene();

		// swap the buffers to present the user the scene
		w.SwapBuffers();

		std::cout << std::endl;
		std::cout << "x abs: " << Mouse::Instance().GetAbsolutePosition().x << std::endl;
		std::cout << "y abs: " << Mouse::Instance().GetAbsolutePosition().y << std::endl;
		std::cout << "x rel: " << Mouse::Instance().GetRelativePosition().x << std::endl;
		std::cout << "y rel: " << Mouse::Instance().GetRelativePosition().y << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// Delete our opengl context, destroy our window, and shutdown SDL
	r.~Renderer();
	w.~Window();
	SDL_Quit();

	return 0;
}