#include "Shader.h"

#include "IntCore.h"

#include <iostream>

Shader::Shader(std::string vertex, std::string fragment)
{
	LoadShader(vertex, GL_VERTEX_SHADER, m_VertexShaderID);
	LoadShader(fragment, GL_FRAGMENT_SHADER, m_FragmentShaderID);

	m_ID = glCreateProgram();

	glAttachShader(m_ID, m_VertexShaderID);
	glAttachShader(m_ID, m_FragmentShaderID);

	glLinkProgram(m_ID);

	GLint status;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLchar infoLog[1024];
		glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
		std::cerr << "shader linking failed: " << infoLog << std::endl;
		return;
	}

	glUseProgram(0);
}

Shader::~Shader()
{
	glUseProgram(0);

	glDetachShader(m_ID, m_VertexShaderID);
	glDetachShader(m_ID, m_FragmentShaderID);

	glDeleteShader(m_FragmentShaderID);
	glDeleteShader(m_VertexShaderID);

	glDeleteProgram(m_ID);
}

void Shader::LoadShader(std::string path, GLuint type, GLuint& id)
{
	std::ifstream file(path);

	std::string source;

	std::string line;
	while (std::getline(file, line))
		source += line + "\n";

	id = glCreateShader(type);

	const char* sourceCstr = source.c_str();
	glShaderSource(id, 1, &sourceCstr, NULL);
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(id, 1024, NULL, infoLog);
		std::cerr << "shader compile failed: " << infoLog << std::endl;
		return;
	}
}

void Shader::Bind()
{
	glUseProgram(m_ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

unsigned int Shader::GetLocation(std::string name)
{
	return (unsigned int) glGetUniformLocation(m_ID, name.c_str());
}

void Shader::Set(unsigned int location, float value)
{
	glUniform1f(location, value);
}

void Shader::Set(unsigned int location, float* value, unsigned int count)
{
	glUniform1fv(location, count, value);
}

void Shader::Set(unsigned int location, int value)
{
	glUniform1i(location, value);
}

void Shader::Set(unsigned int location, int* value, unsigned int count)
{
	glUniform1iv(location, count, value);
}

void Shader::Set(unsigned int location, const glm::vec2& value, unsigned int count)
{
	glUniform2fv(location, count, glm::value_ptr(value));
}

void Shader::Set(unsigned int location, const glm::vec3& value, unsigned int count)
{
	glUniform3fv(location, count, glm::value_ptr(value));
}

void Shader::Set(unsigned int location, const glm::vec4& value, unsigned int count)
{
	glUniform4fv(location, count, glm::value_ptr(value));
}

void Shader::Set(unsigned int location, const glm::mat4& value, unsigned int count)
{
	glUniformMatrix4fv(location, count, GL_FALSE, &value[0][0]);
}

void Shader::Set(std::string name, float value)
{
	Set(GetLocation(name), value);
}

void Shader::Set(std::string name, float* value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}

void Shader::Set(std::string name, int value)
{
	Set(GetLocation(name), value);
}

void Shader::Set(std::string name, int* value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}

void Shader::Set(std::string name, const glm::vec2& value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}

void Shader::Set(std::string name, const glm::vec3& value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}

void Shader::Set(std::string name, const glm::vec4& value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}

void Shader::Set(std::string name, const glm::mat4& value, unsigned int count)
{
	Set(GetLocation(name), value, count);
}
