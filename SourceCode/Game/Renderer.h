#pragma once

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include <glm\glm.hpp>

class Window;

class Renderer {

	public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Constructor.
	/// 		 Creates an OpenGL 3.2 CORE PROFILE rendering context. Sets itself as the
	/// 	current renderer of the passed 'parent' Window.Not the best way to do it - but it kept
	/// 	the Tutorial code down to a minimum!< / summary></summary>
	///
	/// <param name="parent">[in,out] The window class to render to.</param>
	///-------------------------------------------------------------------------------------------------
	Renderer(Window &parent);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Destructor.
	/// 		 Deletes the default shader, and the OpenGL rendering context.</summary>
	///-------------------------------------------------------------------------------------------------
	virtual ~Renderer();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Pure virtual method to define what to render in the scene.</summary>
	///-------------------------------------------------------------------------------------------------
	virtual void RenderScene();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Resizes the rendering area. Should only be called by the Window class!
	///	Does lower bounds checking on input values, so should be reasonably safe
	///		to call.< / summary>
	///
	/// <param name="x">The x coordinate.</param>
	/// <param name="y">The y coordinate.</param>
	///-------------------------------------------------------------------------------------------------
	virtual void Resize(int x, int y);

	protected:


	Mesh* triangle;

	virtual void CheckOpenGLVersion();
	virtual void InitializeGlew();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Updates the global shader uniforms. This
	/// 		 includes e.g. camera positions.
	/// 		 This method can be though of to give you some default uniforms.
	/// 		 Equal to the build-in uniforms in each shader (e.g. gl_FragCoord).</summary>
	///-------------------------------------------------------------------------------------------------
	virtual void UpdateGlobalShaderUniforms();


	///-------------------------------------------------------------------------------------------------
	/// <summary>The shader attached to this renderer.</summary>
	///-------------------------------------------------------------------------------------------------
	Shader* currentShader;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Projection matrix.</summary>
	///-------------------------------------------------------------------------------------------------
	glm::mat4 projectionMatrix;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Model matrix. NOT MODELVIEW.</summary>
	///-------------------------------------------------------------------------------------------------
	glm::mat4 modelMatrix;

	///-------------------------------------------------------------------------------------------------
	/// <summary>View matrix.</summary>
	///-------------------------------------------------------------------------------------------------
	glm::mat4 viewMatrix;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The viewport aspect ratio.</summary>
	///-------------------------------------------------------------------------------------------------
	float aspect;
};