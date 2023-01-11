#include "Shader.hpp"
Shader::Shader() {
	programID = glCreateProgram();
}
void Shader::CreateShader(std::string FileName, GLenum ShaderType, int shader_number) {
	shaders[shader_number] = glCreateShader(ShaderType);
	std::ifstream file(FileName);
	std::string data;
	if (file.is_open())
	{
		char a;
		while ((a = file.get()) != EOF) {
			data += a;
		}
	}
	file.close();
	const char* data_ptr = &data[0];
	glShaderSource(shaders[shader_number],1, &data_ptr, NULL);
	glCompileShader(shaders[shader_number]);
	exception_compile(shaders[shader_number]);
}
void Shader::Attach(int shader_index) {
	glAttachShader(programID, shaders[shader_index]);
}
void Shader::LinkProgram() {
	glLinkProgram(programID);
	exception_link(programID);
}
void Shader::exception_compile(unsigned int shader) {
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(shader, sizeof(errorLog), NULL,errorLog);
		std::cout << std::endl << "Shader Compile Hatasi : " << errorLog;
	}
}
void Shader::exception_link(unsigned int program) {
	
	glGetProgramiv(program, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(program, sizeof(errorLog), NULL,errorLog);
		std::cout << std::endl << "Shader Compile Hatasi : " << errorLog;
	}
}
unsigned int Shader::getProgramID() {
	return programID;
}
void Shader::DeleteShaders() {
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
}
void Shader::DeleteProgram() {
	glDeleteProgram(programID);
}
void Shader::ConnectVariableID(std::string variable) {
	n_map[variable] = glGetUniformLocation(programID, variable.c_str());
}
void Shader::change3f(std::string variable, glm::vec3 position) {
	glUniform3f(n_map[variable], position.x, position.y, position.z);
}void Shader::change4f(std::string variable, glm::vec4 position) {
	glUniform4f(n_map[variable], position.r, position.g, position.b,position.a);
}
