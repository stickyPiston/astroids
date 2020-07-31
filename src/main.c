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
#include <astroids/astroid.h>

#include <stdio.h>
#include <stdlib.h>


// TODO: Split global entities variable into player, bullets and astroids.
struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;
int keys[1024];
int lives = 3;


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
  float astroidTimeout = 1;

  while (!glfwWindowShouldClose(window) && lives > 0) {
    float currentFrame = glfwGetTime();
    float dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (astroidTimeout > 0) {
      astroidTimeout -= dt;
    } else {
      makeAstroid();
      astroidTimeout = 1;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Make collision detection system
    // TODO: Implement text rendering
    // TODO: Make title screen
    // TODO: Make death screen

    handleInput(dt);

    for (int i = 0; i < arrlen(entities.bullets); i++) {
      if (entities.bullets[i].update != NULL) entities.bullets[i].update(i, dt);
      draw(entities.bullets[i]);
    }

    for (int i = 0; i < arrlen(entities.astroids); i++) {
      if (entities.astroids[i].update != NULL) entities.astroids[i].update(i, dt);
      draw(entities.astroids[i]);
    }

    draw(entities.player);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
