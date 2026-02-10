#pragma once

#include <string>
#include <glm/glm.hpp>

void ReadFile(const char *filePath, std::string &outputData);

glm::mat4 TransformationMatrix(const glm::vec3 &pos, const glm::vec3 &rot, float scale);
glm::mat4 ViewMatrix(const glm::vec3 &pos, float pitch, float yaw, float roll);
