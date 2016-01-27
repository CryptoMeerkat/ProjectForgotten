#include "Renderer.h"
#include "Mesh.h"
#include <iostream>

Renderer::Renderer(Window &window) {

	CheckOpenGLVersion();
	InitializeGlew();

	// When we clear the screen, we want it to be dark grey
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// initialize default shader
	currentShader = new Shader("vs.glsl", "fs.glsl");
	if (!currentShader->LinkProgram()) {
		std::cout << "Shader linking no success" << std::endl;
		return;
	}
	glUseProgram(currentShader->GetProgram());

	// Tell our window about the new renderer! (Which will in turn resize the renderer window to fit...)
	window.SetRenderer(this);					

	triangle = Mesh::GenerateTriangle();
}


Renderer::~Renderer() {
	delete triangle;
	glUseProgram(0);
	glDeleteProgram(currentShader->GetProgram());
}

void Renderer::InitializeGlew() {
	// This forces GLEW to give us function pointers for everything (gets around GLEW using 'old fashioned' methods
	// for determining whether a OGL context supports a particular function or not
	glewExperimental = GL_TRUE;

	// Try to initialise GLEW
	if (glewInit() != GLEW_OK) {	
		std::cout << "OGLRenderer::OGLRenderer(): Cannot initialise GLEW!" << std::endl;	//It's all gone wrong!
		return;
	}
	// If we get this far, everything's going well!
}

void Renderer::CheckOpenGLVersion() {
	//Now we have a temporary context, we can find out if we support OGL 3.x
	char* ver = (char*) glGetString(GL_VERSION); // ver must equal "3.2.0" (or greater!)
	int major = ver[0] - '0';		//casts the 'correct' major version integer from our version string
	int minor = ver[2] - '0';		//casts the 'correct' minor version integer from our version string

	if (major < 3) {					//Graphics hardware does not support OGL 3! Erk...
		std::cout << "OGLRenderer::OGLRenderer(): Device does not support OpenGL 3.x!" << std::endl;
	}

	if (major == 3 && minor < 2) {	//Graphics hardware does not support ENOUGH of OGL 3! Erk...
		std::cout << "OGLRenderer::OGLRenderer(): Device does not support OpenGL 3.2!" << std::endl;

	}

	if (major == 4 && minor < 5) {	//Graphics hardware does not support ENOUGH of OGL 4.5
		std::cout << "OGLRenderer::OGLRenderer(): Device does not support OpenGL 4.5!" << std::endl;

	}
	//We do support OGL 3! Let's set it up...
}

void Renderer::RenderScene() {
	// setup clear color for the viewport
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	triangle->Draw();

}

void Renderer::UpdateGlobalShaderUniforms() {

}

void Renderer::Resize(int x, int y) {
	glViewport(0, 0, x, y);
	aspect = float(x) / float(y);
}