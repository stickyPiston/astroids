#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>

#include <astroids/window.h>
#include <astroids/sprite.h>
#include <astroids/error.h>
#include <astroids/input.h>
#include <astroids/resources.h>
#include <astroids/player.h>

#include <stdio.h>
#include <stdlib.h>


// TODO: Split global entities variable into player, bullets and astroids.
struct Sprite *entities = NULL;
int keys[1024] = {};

int main(void) {

  GLFWwindow *window = createWindow();

  glfwSetKeyCallback(window, key_callback);

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

  makePlayer();

  float lastFrame = 0.0;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    float dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Make astroids
    // TODO: Periodically spawn astroids
    // TODO: Add lives variable
    // TODO: Implement text rendering
    // TODO: Make astroids hurt player
    // TODO: Make title screen
    // TODO: Make death screen

    handleInput(dt);

    for (int i = 0; i < arrlen(entities); i++) {
      if (entities[i].update != NULL) entities[i].update(i, dt);
      draw(entities[i]);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
