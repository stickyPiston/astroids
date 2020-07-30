#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <astroids/window.h>
#include <astroids/shader.h>
#include <astroids/quad.h>
#include <astroids/sprite.h>
#include <astroids/resources.h>
#include <astroids/file.h>
#include <astroids/error.h>

#include <stdio.h>
#include <stdlib.h>


int main(void) {

  GLFWwindow *window = createWindow();

  // Uncomment the following line to disable vsync
  //glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    error("Error while initializing GLAD");
    exit(1);
  }

  int screenWidth, screenHeight;
  glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
  glViewport(0, 0, screenWidth, screenHeight);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Initialize all resources (for now, only textures)
  initResources();

  // TODO: Make the player moveable

  // Load necessary components for a sprite.
  struct Shape quad = generateQuad();
  char *vertexShaderSource = readFile("src/shaders/vertex.glsl");
  char *fragmentShaderSource = readFile("src/shaders/fragment.glsl");
  unsigned int program = generateShaders(vertexShaderSource, fragmentShaderSource);
  unsigned int texture = getResource("player");

  struct Sprite sprite = {
    quad,       // shape
    texture,    // texture
    program,    // shaders
    0.5,        // x 
    0.5,        // y
    0.03,       // width
    0.05        // height
  };

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    draw(sprite);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
