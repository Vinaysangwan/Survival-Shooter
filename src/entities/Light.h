#pragma once

#include <glm/glm.hpp>

class Light
{
public:
  Light(const glm::vec3 &pos, const glm::vec3 &color);
  ~Light();

  inline const glm::vec3 &GetPosition() const { return m_Pos; }
  inline const glm::vec3 &GetColor() const { return m_Color; }

private:
  glm::vec3 m_Pos;
  glm::vec3 m_Color;
};
