#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
  Camera(const glm::vec3 &pos, float pitch, float yaw, float roll);
  ~Camera();

  void move();
  
  inline const glm::vec3 &GetPosition() const { return m_Pos; }
  inline float GetPitch() const { return m_Pitch; }
  inline float GetYaw() const { return m_Yaw; }
  inline float GetRoll() const { return m_Roll; }

private:
  glm::vec3 m_Pos;
  float m_Pitch;
  float m_Yaw;
  float m_Roll;
};
