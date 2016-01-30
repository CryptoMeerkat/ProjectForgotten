#include "Renderer.h"
#include "Mesh.h"
#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Renderer::Renderer(Window &window) {

	CheckOpenGLVersion();
	InitializeGlew();
	
	// initialize default shader
	currentShader = new Shader("vs.glsl", "fs.glsl");
	if (!currentShader->LinkProgram()) {
		std::cout << "Shader linking: Failed!" << std::endl;
		return;
	}

	// Tell our window about the new renderer! (Which will in turn resize the renderer window to fit...)
	window.SetRenderer(this);					

	triangle = Mesh::GenerateTriangle();

	Resize(512, 512);
}


Renderer::~Renderer() {
	delete triangle;
	glDeleteProgram(currentShader->GetProgram());
}

void Renderer::InitializeGlew() {
	// This forces GLEW to give us function pointers for everything (gets around GLEW using 'old fashioned' methods
	// for determining whether a OGL context supports a particular function or not
	glewExperimental = GL_TRUE;

	// Try to initialise GLEW
	if (glewInit() != GLEW_OK) {	
		std::cout << "GLEW init: Failed!" << std::endl;	//It's all gone wrong!
		return;
	}
	// If we get this far, everything's going well!
}

void Renderer::CheckOpenGLVersion() {
	char* ver = (char*) glGetString(GL_VERSION); // ver must equal "3.2.0" (or greater!)
	int major = ver[0] - '0';		//casts the 'correct' major version integer from our version string
	int minor = ver[2] - '0';		//casts the 'correct' minor version integer from our version string

	if (major < 3) {
		std::cout << "Device does not support OpenGL 3.x!" << std::endl;
	} else if (major == 3 && minor < 2) {
		std::cout << "Device does not support OpenGL 3.2!" << std::endl;
	} else if (major == 4 && minor < 4) {
		std::cout << "Device does not support OpenGL 4.4!" << std::endl;
	} else if (major == 4 && minor < 5) {
		std::cout << "Device does not support OpenGL 4.5!" << std::endl;
	}

}

void Renderer::RenderScene() {

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(currentShader->GetProgram());
	UpdateGlobalShaderUniforms();

	// setup clear color for the viewport
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	triangle->Draw();


	glUseProgram(0);

}

void Renderer::UpdateScene(float msec) {
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::UpdateGlobalShaderUniforms() {

	//projectionMatrix = glm::mat4(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 15000.0f));
	projectionMatrix = glm::mat4(glm::perspective(45.0f, aspect, 1.0f, 15000.0f));
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Renderer::Resize(int x, int y) {
	glViewport(0, 0, x, y);
	aspect = float(x) / float(y);
}