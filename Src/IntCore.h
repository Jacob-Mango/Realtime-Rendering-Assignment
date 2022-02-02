#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Binding.h"
#include "Logging.h"
#include "Reference.h"

#define GL_ERROR()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
		GLenum error = glGetError();                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
		if (error != GL_NO_ERROR)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
			std::cerr << "[OpenGL Error] (" << std::to_string(error) << "): "                                                                                                                                                                                                                                                                                                                                                                                                                                      \
					  << "\t" << __FILE__ << ":" << __LINE__ << std::endl;                                                                                                                                                                                                                                                                                                                                                                                                                                         \
	}