#include <GLFW/glfw3.h>
#include <stb/stb_ds.h>

#include <astroids/sprite.h>
#include <astroids/file.h>
#include <astroids/resources.h>
#include <astroids/shader.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Sprite *entities;
int keys[1024];
float shootTimeout = 0;

#define PI 3.1415

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS) {
      keys[key] = 1;
    } else if (action == GLFW_RELEASE) {
      keys[key] = 0;
    }
  }
}

static void bullet_update(int index) {
  float speed = 0.01;

  // Transform a first, because openGL messes up the rotations for whatever reason.
  float a = (entities[index].rotation - 1.57) + PI;//(1 / 2) * PI);

  entities[index].x += speed * cos(a);
  entities[index].y += speed * sin(a);
}

void handleInput(float dt) {
  if (keys[GLFW_KEY_RIGHT]) {
    entities[0].rotation -= 0.1;
  }

  if (keys[GLFW_KEY_LEFT]) {
    entities[0].rotation += 0.1;
  }

  if (keys[GLFW_KEY_UP]) {
    float speed = 0.01;

    // Transform a first, because openGL messes up the rotations for whatever reason.
    float a = (entities[0].rotation - 1.57) + PI;//(1 / 2) * PI);

    entities[0].x += speed * cos(a);
    entities[0].y += speed * sin(a);
  }

  if (keys[GLFW_KEY_SPACE] && shootTimeout <= 0) {
    shootTimeout = 0.5;
    // FIXME: Add shaders to resource manager
    // FIXME: Add quad to resource manager
    struct Shape quad = generateQuad();
    char *vertexShaderSource = readFile("src/shaders/vertex.glsl");
    char *fragmentShaderSource = readFile("src/shaders/fragment.glsl");
    unsigned int program = generateShaders(vertexShaderSource, fragmentShaderSource);
    unsigned int texture = getResource("player");

    struct Sprite sprite = {
      quad,                 // shape
      texture,              // texture
      program,              // shaders
      entities[0].x,        // x 
      entities[0].y,        // y
      0.03,                 // width
      0.03,                 // height
      entities[0].rotation, // rotation
      bullet_update
    };
    arrput(entities, sprite);
  }

  if (shootTimeout > 0) shootTimeout -= dt;
}
