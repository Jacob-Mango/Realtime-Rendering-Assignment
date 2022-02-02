#pragma once

#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sdl/SDL.h>
#include <string>
#include <vector>

#include "Reference.h"

class Shader : public Countable
{
	GLuint m_ID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;

public:
	Shader(std::string vertex, std::string fragment);
	virtual ~Shader();

	void Bind();
	void Unbind();

	unsigned int GetLocation(std::string name);

	void Set(unsigned int location, float value);
	void Set(unsigned int location, float* value, unsigned int count);
	void Set(unsigned int location, int value);
	void Set(unsigned int location, int* value, unsigned int count);
	void Set(unsigned int location, const glm::vec2& value, unsigned int count = 1);
	void Set(unsigned int location, const glm::vec3& value, unsigned int count = 1);
	void Set(unsigned int location, const glm::vec4& value, unsigned int count = 1);
	void Set(unsigned int location, const glm::mat4& value, unsigned int count = 1);

	void Set(std::string name, float value);
	void Set(std::string name, float* value, unsigned int count);
	void Set(std::string name, int value);
	void Set(std::string name, int* value, unsigned int count);
	void Set(std::string name, const glm::vec2& value, unsigned int count = 1);
	void Set(std::string name, const glm::vec3& value, unsigned int count = 1);
	void Set(std::string name, const glm::vec4& value, unsigned int count = 1);
	void Set(std::string name, const glm::mat4& value, unsigned int count = 1);

private:
	void LoadShader(std::string path, GLuint type, GLuint& id);
};
