#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::ostream& operator<<(std::ostream& os, const glm::vec2& value);
std::ostream& operator<<(std::ostream& os, const glm::dvec2& value);
std::ostream& operator<<(std::ostream& os, const glm::vec3& value);
std::ostream& operator<<(std::ostream& os, const glm::dvec3& value);
std::ostream& operator<<(std::ostream& os, const glm::vec4& value);
std::ostream& operator<<(std::ostream& os, const glm::dvec4& value);
std::ostream& operator<<(std::ostream& os, const glm::mat4& value);
std::ostream& operator<<(std::ostream& os, const glm::mat3& value);
std::ostream& operator<<(std::ostream& os, const glm::quat& value);