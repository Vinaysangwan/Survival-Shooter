#include "pch.h"
#include "Utils.h"
#include "core/Logger.h"

void ReadFile(const char *filePath, std::string &outputData)
{
  std::ifstream file(filePath);

  if (file.is_open())
  {
    std::string line;
    while (std::getline(file, line))
    {
      outputData.append(line);
      outputData.append("\n");
    }

    file.close();
  }
  else
  {
    LOG_ASSERT(false, "Failed to Open the File: {}", filePath);
  }
}

glm::mat4 TransformationMatrix(const glm::vec3 &pos, const glm::vec3 &rot, float scale)
{
  glm::mat4 trans = glm::mat4(1.0f);
  
  trans = glm::translate(trans, pos);

  trans = glm::rotate(trans, glm::radians(rot.x), glm::vec3(1, 0, 0));
  trans = glm::rotate(trans, glm::radians(rot.y), glm::vec3(0, 1, 0));
  trans = glm::rotate(trans, glm::radians(rot.z), glm::vec3(0, 0, 1));
  
  trans = glm::scale(trans, glm::vec3(scale));

  return trans;
}
