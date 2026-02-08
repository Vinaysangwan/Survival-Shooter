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