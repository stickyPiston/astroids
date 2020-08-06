#include <GLFW/glfw3.h>
#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <astroids/sprite.h>
#include <astroids/resources.h>
#include <astroids/bullet.h>
#include <astroids/player.h>
#include <astroids/state.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;
int keys[1024];
enum State gameState;

float shootTimeout = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS) {
      keys[key] = 1;
    } else if (action == GLFW_RELEASE) {
      keys[key] = 0;
    }
  }
}

void handleInput(float dt) {
  if (gameState == STATE_GAME) {
    if (keys[GLFW_KEY_RIGHT]) {
      entities.player.rotation -= 3.5 * dt;
    }

    if (keys[GLFW_KEY_LEFT]) {
      entities.player.rotation += 3.5 * dt;
    }

    if (keys[GLFW_KEY_UP]) {
      float speed = 1;

      // Transform a first, because openGL messes up the rotations for whatever reason.
      float a = (entities.player.rotation - 1.57) + M_PI;

      entities.player.x += speed * cos(a) * dt;
      entities.player.y += speed * sin(a) * dt;
    }

    if (keys[GLFW_KEY_SPACE] && shootTimeout <= 0) {
      shootTimeout = 0.5;

      makeBullet();
    }

    if (shootTimeout > 0) shootTimeout -= dt;
  } else if (gameState == STATE_MAIN_MENU) {
    if (keys[GLFW_KEY_SPACE]) {
      gameState = STATE_GAME;
      makePlayer();
    }
  }
}
