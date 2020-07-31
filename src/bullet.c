#include <stb/stb_ds.h>

#include <astroids/resources.h>
#include <astroids/sprite.h>

#include <math.h>

struct Sprite *entities;

static void bullet_update(int index, float dt) {
  float speed = 2;

  // Transform a first, because openGL messes up the rotations for whatever reason.
  float a = (entities[index].rotation - 1.57) + M_PI;

  entities[index].x += speed * cos(a) * dt;
  entities[index].y += speed * sin(a) * dt;

  if (
       entities[index].x > 1
    || entities[index].x < -1
    || entities[index].y > 1
    || entities[index].y < -1
  ) {
    arrdel(entities, index);
  }
}

void makeBullet() {
  struct Shape quad = getShape();
  unsigned int shader = getShader();
  unsigned int texture = getTexture("player");

  struct Sprite sprite = {
    quad,                 // shape
    texture,              // texture
    shader,               // shaders
    entities[0].x,        // x 
    entities[0].y,        // y
    0.03,                 // width
    0.03,                 // height
    entities[0].rotation, // rotation
    bullet_update         // update
  };

  arrput(entities, sprite);
}
