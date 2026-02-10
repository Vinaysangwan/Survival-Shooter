#include "Input.h"

// #############################################################################
//                           Constants
// #############################################################################
constexpr const int MAX_KEY_COUNT = GLFW_KEY_LAST;

// #############################################################################
//                           Structs
// #############################################################################
struct Keyboard
{
  bool keys[MAX_KEY_COUNT + 1] = {};
  bool prevKeys[MAX_KEY_COUNT + 1] = {};
};

// #############################################################################
//                           Globals
// #############################################################################
static Keyboard keyboard;

// #############################################################################
//                           Callbacks
// #############################################################################
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key >= 0 && key <= MAX_KEY_COUNT)
  {
    if (action == GLFW_PRESS)
    {
      keyboard.keys[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
      keyboard.keys[key] = false;
    }
  }
}

// #############################################################################
//                           Functions
// #############################################################################
bool KeyDown(int key)
{
  if (key >= 0 && key <= MAX_KEY_COUNT)
  {
    return keyboard.keys[key];
  }
  return false;
}

bool KeyPressed(int key)
{
  if (key >= 0 && key <= MAX_KEY_COUNT)
  {
    return keyboard.keys[key] && !keyboard.prevKeys[key];
  }
  return false;
}

bool keyReleased(int key)
{
  if (key >= 0 && key <= MAX_KEY_COUNT)
  {
    return !keyboard.keys[key] && keyboard.prevKeys[key];
  }
  return false;
}

void KeyboardEndFrame()
{
  for (int i = 0; i <= MAX_KEY_COUNT; i++)
  {
    keyboard.prevKeys[i] = keyboard.keys[i];
  }
}
