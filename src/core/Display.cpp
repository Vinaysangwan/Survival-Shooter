#include "pch.h"
#include "Display.h"

#include "Logger.h"

Display::Display(const char *title, int width, int height, bool isResizable)
  : m_Width(width), m_Height(height)
{
  // Init GLfw
  if (!glfwInit())
  {
    LOG_ASSERT(false, "Failed to Init GLFW!");
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
    LOG_ASSERT(false, "Failed to Create Window");
  }

  m_LastTime = glfwGetTime();

  // Set Window Pos
  const GLFWvidmode* vdMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(m_Window, (vdMode->width - width) / 2, (vdMode->height - height + 40) / 2);
  
  glfwMakeContextCurrent(m_Window);

  // Init GLAD
  if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
  {
    LOG_ASSERT(false, "Failed to Load GLAD");
  }

  // OpenGL Viewport
  glViewport(0, 0, width, height);

  // gl Enables
  glEnable(GL_FRAMEBUFFER_SRGB);

  // Show Window
  glfwShowWindow(m_Window);
}

Display::~Display()
{
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

void Display::Update()
{
  double currentTime = glfwGetTime();
  m_Delta = static_cast<float>(currentTime - m_LastTime);
  m_LastTime = currentTime;

  m_FrameCount++;
  
  glfwPollEvents();
}

void Display::SwapBuffers() const
{
  glfwSwapBuffers(m_Window);
}
