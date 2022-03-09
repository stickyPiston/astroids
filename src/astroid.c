#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <astroids/resources.h>
#include <astroids/sprite.h>
#include <astroids/state.h>

#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

extern struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;
extern int lives;
extern enum State gameState;

static void astroid_update(int index, float dt) {
  float speed = 0.5;

  // Transform a first, because openGL messes up the rotations for whatever reason.
  float a = (entities.astroids[index].rotation - 1.57) + M_PI;

  entities.astroids[index].x += speed * cos(a) * dt;
  entities.astroids[index].y += speed * sin(a) * dt;

  struct Sprite player = entities.player;
  struct Sprite astroid = entities.astroids[index];
  int hit = 0;
  if (
       gameState == STATE_GAME
    && player.x + player.width >= astroid.x
    && player.x <= astroid.x + 0.9 * astroid.width
    && player.y + player.height >= astroid.y
    && player.y <= astroid.y + 0.9 * astroid.height
  ) {
    hit = 1;
    lives--;
    arrdel(entities.astroids, index);
  }

  if (
       !hit
    && (
       entities.astroids[index].x > 1
    || entities.astroids[index].x < -1
    || entities.astroids[index].y > 1
    || entities.astroids[index].y < -1
    )
  ) {
    arrdel(entities.astroids, index);
  }
}

void makeAstroid() {
  struct Shape quad = getShape();
  unsigned int shader = getShader();

  // Pick one random texture
  srand(time(NULL));

  char *textureName = malloc(32);
  char *textureIndex = malloc(8);

  strcpy(textureName, "");
  strcpy(textureIndex, "");

  int ti = rand() % 5 + 1;
  strcat(textureName, "astroid");
  sprintf(textureIndex, "%d", ti);
  strcat(textureName, textureIndex);

  unsigned int texture = getTexture(textureName);

  free(textureName);
  free(textureIndex);

  // Randomize x and y position
  
  // Choose axis. X = 1, Y = 2
  int axis = rand() > ((float)RAND_MAX / 2) ? 1 : 2;

  float x, y;
  if (axis == 1) {
    x = 2 * ((float)rand() / (float)RAND_MAX) - 1;
    y = rand() > ((float)RAND_MAX / 2) ? 1 : -1;
  } else {
    x = rand() > ((float)RAND_MAX / 2) ? 1 : -1;
    y = 2 * ((float)rand() / (float)RAND_MAX) - 1;
  }

  // Randomize rotation
  float rotation = (0.5 * M_PI) * ((float)rand() / (float)RAND_MAX);

  if (x < 0 && y > 0) {
    rotation += M_PI;
  } else if (x < 0 && y < 0) {
    rotation += 1.5 * M_PI;
  } else if (x >= 0 && y < 0) {
    rotation += 0;
  } else if (x >= 0 && y > 0) {
    rotation += 0.5 * M_PI;
  }

  // Randomize size
  float size = 0.03 + 0.1 * ((float)rand() / (float)RAND_MAX);

  struct Sprite sprite = {
    quad,                 // shape
    texture,              // texture
    shader,               // shaders
    x,                    // x 
    y,                    // y
    size,                 // width
    size,                 // height
    rotation,             // rotation
    astroid_update        // update
  };

  arrput(entities.astroids, sprite);
}
