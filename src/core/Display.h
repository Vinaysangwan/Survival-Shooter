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

  void Update() const;
  void SwapBuffers() const;

  inline bool IsRunning() const { return !glfwWindowShouldClose(m_Window); }

  inline void SetVsync(bool vSync) const { glfwSwapInterval(vSync ? 1 : 0); }

private:
  GLFWwindow *m_Window;
  
  int m_Height;
  int m_Width;
};
