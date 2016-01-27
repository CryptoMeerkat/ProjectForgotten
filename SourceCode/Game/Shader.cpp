#include "Shader.h"
#include <istream>
#include <iostream>
#include <string>
#include <fstream>

#include "MeshBuffer.h"

GLuint Shader::GetProgram() {
	return program;
}

Shader::Shader(std::string vFile, std::string fFile, std::string name, std::string gFile, std::string tcFile, std::string teFile) {
	//shaders are attached to a program
	program = glCreateProgram();

	objects[SHADER_VERTEX] = GenerateShader(vFile, GL_VERTEX_SHADER);
	objects[SHADER_FRAGMENT] = GenerateShader(fFile, GL_FRAGMENT_SHADER);
	objects[SHADER_GEOMETRY] = 0;
	objects[SHADER_TESSELATION_CONTROL] = 0;
	objects[SHADER_TESSELATION_EVALUATION] = 0;

	if (!gFile.empty()) {
		objects[SHADER_GEOMETRY] = GenerateShader(gFile, GL_GEOMETRY_SHADER);
		glAttachShader(program, objects[SHADER_GEOMETRY]);
	}

	if (!tcFile.empty()) {
		objects[SHADER_TESSELATION_CONTROL] = GenerateShader(tcFile, GL_TESS_CONTROL_SHADER);
		glAttachShader(program, objects[SHADER_TESSELATION_CONTROL]);
	}

	if (!teFile.empty()) {
		objects[SHADER_TESSELATION_EVALUATION] = GenerateShader(teFile, GL_TESS_EVALUATION_SHADER);
		glAttachShader(program, objects[SHADER_TESSELATION_EVALUATION]);
	}

	glAttachShader(program, objects[SHADER_VERTEX]);
	glAttachShader(program, objects[SHADER_FRAGMENT]);

	this->updateShaderUniforms = [] {};
	this->name = name;
	SetDefaultAttributes();
}

Shader::~Shader(void) {
	for (int i = 0; i < 5; i++) {
		//Should throw a GL_INVALID_VALUE error for the geometry shader if not given
		glDetachShader(program, objects[i]);
		glDeleteShader(objects[i]);
	}

	glDeleteProgram(program);
}

GLuint Shader::GenerateShader(std::string from, GLenum type) {

	std::cout << "Compiling Shader..." << std::endl;

	//load the shader file into a string
	std::string load;
	if (!LoadShaderFile(from, load)) {
		std::cout << "Compiling failed!" << std::endl;
		loadFailed = true;
		return 0;
	}

	GLuint shader = glCreateShader(type);
	const char* chars = load.c_str();

	//load the shader source into OGL
	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	//fetch the compiler status for the compiling process of the shader
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	//check the compiler status for the shader
	if (status == GL_FALSE) {
		std::cout << "Compiling failed!" << std::endl;
		char error[512];
		glGetInfoLogARB(shader, sizeof(error), NULL, error);
		std::cout << error;
		loadFailed = true;
		return 0;
	}

	std::cout << "Compiling success!" << std::endl;
	loadFailed = false;
	return shader;
}

bool Shader::LoadShaderFile(std::string from, std::string &into) {
	std::ifstream file;
	std::string tmp;

	std::cout << "Loading shader text from " << from << std::endl << std::endl;

	file.open(from.c_str());
	if (!file.is_open()) {
		std::cout << "File does not exists!" << std::endl;
		return false;
	}

	while (!file.eof()) {
		getline(file, tmp);
		into += tmp + "\n";
	}

	file.close();
	//std::cout << into << std::endl << std::endl;
	//std::cout << "Loaded shader text!" << std::endl << std::endl;
	return true;

}

void Shader::SetDefaultAttributes() {
	//these calls bind the given indexes into the vertex shader
	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, COLOUR_BUFFER, "color");
	//even if no texture coords are attached, it will work
	//glBindAttribLocation(program, TEXTURE_BUFFER, "texCoord");
	////normals and tangents will be used for lightning
	//glBindAttribLocation(program, NORMAL_BUFFER, "normal");
	////tanget is used for appropriate bump mapping
	//glBindAttribLocation(program, TANGENT_BUFFER, "tangent");
}


bool Shader::LinkProgram() {
	if (loadFailed) {
		return false;
	}

	glLinkProgram(program);

	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);
	return code == GL_TRUE;
}

void Shader::SetShaderUniformLoader(std::function<void()> func) {
	updateShaderUniforms = func;
}

void Shader::UpdateShaderUniforms() {
	updateShaderUniforms();
}