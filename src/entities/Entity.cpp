#include "Entity.h"
#include "inputs/Input.h"

Entity::Entity(const TexturedModel &model, const glm::vec3 &pos, const glm::vec3 &rot, float scale)
  : m_Model(model), m_Pos(pos), m_Rot(rot), m_Scale(scale)
{
}

Entity::~Entity()
{
}

void Entity::rotate(float rx, float ry, float rz)
{
  m_Rot.x += rx;
  m_Rot.y += ry;
  m_Rot.z += rz;
}

void Entity::move()
{
  if (KeyDown(GLFW_KEY_LEFT))
  {
    m_Rot.y -= 1;
  }
  if (KeyDown(GLFW_KEY_RIGHT))
  {
    m_Rot.y += 1;
  }
  if (KeyDown(GLFW_KEY_UP))
  {
    m_Rot.x += 1;
  }
  if (KeyDown(GLFW_KEY_DOWN))
  {
    m_Rot.x -= 1;
  }
  if (KeyDown(GLFW_KEY_R))
  {
    m_Rot.x = 0;
    m_Rot.y = 0;
  }
}

const TexturedModel &Entity::GetModel() const
{
  return m_Model;
}

const glm::vec3 &Entity::GetPosition() const
{
  return m_Pos;
}

const glm::vec3 &Entity::GetRotation() const
{
  return m_Rot;
}

float Entity::GetScale() const
{
  return m_Scale;
}
