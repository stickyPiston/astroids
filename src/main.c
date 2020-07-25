#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

void errorCallback(int error, const char* description) {
  fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

GLFWwindow *initialize() {
  int glfwInitRes = glfwInit();
  if (!glfwInitRes) {
    perror("Unable to initialize GLFW\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", NULL, NULL);
  if (!window) {
    perror("Unable to create GLFW window\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  int gladInitRes = gladLoadGL();
  if (!gladInitRes) {
    perror("Unable to initialize glad\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return NULL;
  }

  return window;
}


int main(int argc, char* argv[]) {
   glfwSetErrorCallback(errorCallback);

   GLFWwindow* window = initialize();
   if (!window) {
     return 0;
   }

   // Set the clear color to a nice green
   glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

   while (!glfwWindowShouldClose(window)) {
     glClear(GL_COLOR_BUFFER_BIT);

     glfwSwapBuffers(window);
     glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}
