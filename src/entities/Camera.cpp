#include "Camera.h"
#include "inputs/Input.h"

constexpr const float SPEED = 0.08f;

Camera::Camera(const glm::vec3 &pos, float pitch, float yaw, float roll)
  : m_Pos(pos), m_Pitch(pitch), m_Yaw(yaw), m_Roll(roll)
{
}

Camera::~Camera()
{
}

void Camera::move()
{
  if (KeyDown(GLFW_KEY_W))
  {
    m_Pos.z -= SPEED;
  }
  if (KeyDown(GLFW_KEY_S))
  {
    m_Pos.z += SPEED;
  }
  if (KeyDown(GLFW_KEY_A))
  {
    m_Pos.x -= SPEED;
  }
  if (KeyDown(GLFW_KEY_D))
  {
    m_Pos.x += SPEED;
  }
  if (KeyDown(GLFW_KEY_E))
  {
    m_Pos.y += SPEED;
  }
  if (KeyDown(GLFW_KEY_Q))
  {
    m_Pos.y -= SPEED;
  }
}
