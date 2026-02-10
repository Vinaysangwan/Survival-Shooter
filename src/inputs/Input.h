#pragma once

#include <GLFW/glfw3.h>

// #############################################################################
//                           Callbacks
// #############################################################################
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

// #############################################################################
//                           Functions
// #############################################################################
bool KeyDown(int key);

bool KeyPressed(int key);

bool keyReleased(int key);

void KeyboardEndFrame();
