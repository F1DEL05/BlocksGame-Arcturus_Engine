#ifndef SHADER_HPP
#define SHADER_HPP
#include<iostream>
#include<gl/glew.h>
#include<map>
#include<fstream>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Shader {
public:
	Shader();
	void CreateShader(std::string FileName, GLenum ShaderType,int shader_number);
	void Attach(int shader_index);
	void LinkProgram();
	unsigned int getProgramID();
	void DeleteShaders();
	void DeleteProgram();


	//moving functions
	void ConnectVariableID(std::string variable);
	void change3f(std::string variable,glm::vec3 position);
	void change4f(std::string variable,glm::vec4 position);

private:
	void exception_compile(unsigned int shader);
	void exception_link(unsigned int program);
	std::map<std::string, int> n_map;
	int programID;
	unsigned int shaders[2];
	int succes = 1;
	char errorLog[200] = { 0 };
};
#endif // !SHADER_HPP
