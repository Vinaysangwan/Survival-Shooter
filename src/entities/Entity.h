#pragma once

#include <glm/glm.hpp>

#include "models/Models.h"

class Entity
{
public:
  Entity(const TexturedModel &model, const glm::vec3 &pos, const glm::vec3 &rot, float scale);
  ~Entity();

  void rotate(float rx, float ry, float rz);
  void move(float dx, float dy, float dz);
  
  const TexturedModel &GetModel() const;
  const glm::vec3 &GetPosition() const;
  const glm::vec3 &GetRotation() const;
  float GetScale() const;

private:
  TexturedModel m_Model;

  glm::vec3 m_Pos;
  glm::vec3 m_Rot;
  float m_Scale;
};
