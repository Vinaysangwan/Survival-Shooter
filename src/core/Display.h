#pragma once

#include <GLFW/glfw3.h>

// #############################################################################
//                           Functions
// #############################################################################
class Display
{
public:
  Display(const char *title, int width, int height, bool isResizable = false);
  ~Display();

  void Update();
  void SwapBuffers() const;

  inline void SetVsync(bool vSync)
  {
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(vSync ? 1 : 0); 
  }

  inline void close() const { glfwSetWindowShouldClose(m_Window, true); }

  inline bool IsRunning() const { return !glfwWindowShouldClose(m_Window); }
  inline float getDelta() const { return m_Delta; }
  inline int getFrameCount() const { return m_FrameCount; }

private:
  GLFWwindow *m_Window;
  
  int m_Height;
  int m_Width;

  float m_Delta{};
  double m_LastTime;

  float m_FrameTimer{};
  int m_FrameCount{};
};
