#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <astroids/window.h>
#include <astroids/sprite.h>
#include <astroids/error.h>
#include <astroids/input.h>
#include <astroids/resources.h>
#include <astroids/player.h>
#include <astroids/astroid.h>
#include <astroids/state.h>
#include <astroids/titles.h>
#include <astroids/score.h>
#include <astroids/lives.h>

#include <stdio.h>
#include <stdlib.h>


// TODO: Move global variables into own header
struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;
int keys[1024];
int lives = 3;
enum State gameState = STATE_MAIN_MENU;
int score;


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

  // Initialize all resources
  initResources();

  float lastFrame = 0.0;
  float astroidTimeout = 1;
  float pressStartBlinkingInterval = 0.8;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    float dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    if (astroidTimeout > 0) {
      astroidTimeout -= dt;
    } else {
      makeAstroid();
      astroidTimeout = 1;
    }

    // TODO: Make death screen

    handleInput(dt);

    for (int i = 0; i < arrlen(entities.astroids); i++) {
      entities.astroids[i].update(i, dt);
      draw(entities.astroids[i]);
    }

    // TODO: Move game loop into separate file
    if (gameState == STATE_GAME) {
      // TODO: Add score and lives meters
      // TODO: Make function for displaying digits
      for (int i = 0; i < arrlen(entities.bullets); i++) {
        entities.bullets[i].update(i, dt);
        draw(entities.bullets[i]);
      }

      draw(getLivesTitle());
      draw(getScoreTitle());

      struct Sprite *digits = displayScore();
      for (int i = 0; i < arrlen(digits); i++) {
        draw(digits[i]);
      }
      arrfree(digits);

      draw(displayLives());

      if (entities.player.width != 0) draw(entities.player);
    } else if (gameState == STATE_MAIN_MENU) {
      draw(getTitle());

      pressStartBlinkingInterval -= dt;
      if (pressStartBlinkingInterval > 0) draw(getPressStart());
      if (pressStartBlinkingInterval < -0.8) pressStartBlinkingInterval = 0.8;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
