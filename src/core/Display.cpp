#include "pch.h"
#include "Display.h"

Display::Display(const char *title, int width, int height, bool isResizable)
  : m_Width(width), m_Height(height)
{
  // Init GLfw
  if (!glfwInit())
  {
    std::cerr<<"Falied to Init GLfw"<<std::endl;
  }

  // Window Hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, isResizable ? 1 : 0);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  // Window Creation
  m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!m_Window)
  {
    std::cerr<<"Failed to Create Window"<<std::endl;
  }

  // Set Window Pos
  const GLFWvidmode* vdMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(m_Window, (vdMode->width - width) / 2, (vdMode->height - height + 40) / 2);
  
  glfwMakeContextCurrent(m_Window);

  // Init GLAD
  if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
  {
    std::cerr<<"Failed to Load Glad"<<std::endl;
  }

  // OpenGL Viewport
  glViewport(0, 0, width, height);

  // Show Window
  glfwShowWindow(m_Window);
}

Display::~Display()
{
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

void Display::Update() const
{
  glfwPollEvents();
}

void Display::SwapBuffers() const
{
  glfwSwapBuffers(m_Window);
}
