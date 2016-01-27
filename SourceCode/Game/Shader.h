#pragma once

#include <GL\glew.h>
#include <functional>

//the indices for the different shaders
#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2
#define SHADER_TESSELATION_CONTROL 3
#define SHADER_TESSELATION_EVALUATION 4

///-------------------------------------------------------------------------------------------------
/// <summary>The shader class is responsible to handle different shaders and
/// 		 push data to them.</summary>
///-------------------------------------------------------------------------------------------------
class Shader {

	public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Constructor.</summary>
	///
	/// <param name="vertex">			 The vertex shader file path.</param>
	/// <param name="fragment">			 The fragment shader file path.</param>
	/// <param name="name">				 The name.</param>
	/// <param name="geometry">			 The geometry shader file path.</param>
	/// <param name="tesselationControl">	Tesselation control shader path.</param>
	/// <param name="tesselationEval">   The tesselation evaluation shader path.</param>
	///-------------------------------------------------------------------------------------------------
	Shader(std::string vertex, std::string fragment, std::string name = "(no name)", std::string geometry = "", std::string tesselationControl = "", std::string tesselationEval = "");

	///-------------------------------------------------------------------------------------------------
	/// <summary>Destructor.</summary>
	///-------------------------------------------------------------------------------------------------
	~Shader();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns the program.</summary>
	///
	/// <returns>The program.</returns>
	///-------------------------------------------------------------------------------------------------
	GLuint GetProgram();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Links the program.</summary>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	///-------------------------------------------------------------------------------------------------
	bool LinkProgram();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Loads/Updates the uniforms with the internal lambda function.</summary>
	///-------------------------------------------------------------------------------------------------
	void UpdateShaderUniforms();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Updates the lambda function to update the uniforms.</summary>
	///
	/// <param name="func">The lambda function defining the update of the uniforms.</param>
	///-------------------------------------------------------------------------------------------------
	void SetShaderUniformLoader(std::function<void()> func);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the name.</summary>
	///
	/// <returns>The name.</returns>
	///-------------------------------------------------------------------------------------------------
	std::string GetName() const {
		return name;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets the name.</summary>
	///
	/// <param name="val">The new name.</param>
	///-------------------------------------------------------------------------------------------------
	void SetName(std::string val) {
		name = val;
	}

	protected:


	///-------------------------------------------------------------------------------------------------
	/// <summary>Default shader bindings are set.</summary>
	///-------------------------------------------------------------------------------------------------
	void SetDefaultAttributes();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Loads the given file "from" into the "into" argument.</summary>
	///
	/// <param name="from">Source for the shader file.</param>
	/// <param name="into">[in,out] The file where to write the shader to.</param>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	///-------------------------------------------------------------------------------------------------
	bool LoadShaderFile(std::string from, std::string &into);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Generates a shader of the given type from the given file.</summary>
	///
	/// <param name="from">Source for the shader.</param>
	/// <param name="type">The type of the shader.</param>
	///
	/// <returns>The shader name.</returns>
	///-------------------------------------------------------------------------------------------------
	GLuint GenerateShader(std::string from, GLenum type);

	///-------------------------------------------------------------------------------------------------
	/// <summary>The shader objects are hold in here.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint objects[5];

	///-------------------------------------------------------------------------------------------------
	/// <summary>The OGL program bound with the shaders.</summary>
	///-------------------------------------------------------------------------------------------------
	GLuint program;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The name of this shader.
	/// 		 THis is only one name for all the shader files attached to this Shader
	/// 		 object. But it is enough for the first time.</summary>
	///-------------------------------------------------------------------------------------------------
	std::string name;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Indicator whether or not the shader loading failed at some point.</summary>
	///-------------------------------------------------------------------------------------------------
	bool loadFailed;

	///-------------------------------------------------------------------------------------------------
	/// <summary>This lambda function is used to setup shader uniforms.
	/// 		 This function must be set for every shader. It can be of course just be empty.</summary>
	///-------------------------------------------------------------------------------------------------
	std::function<void()> updateShaderUniforms;

};