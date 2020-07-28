#include <GLFW/glfw3.h>

#include <astroids/error.h>

#include <stdio.h>
#include <stdlib.h>

GLFWwindow *createWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  GLFWwindow *window = glfwCreateWindow(1280, 960, "Hello, world!", NULL, NULL);

  if (window == NULL) {
    error("Could not create a window");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);

  return window;
}
