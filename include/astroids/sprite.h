#ifndef SPRITE_H
#define SPRITE_H

#include <astroids/quad.h>

struct Sprite {
  struct Shape shape;
  unsigned int texture;
  unsigned int program;

  float x;
  float y;

  float width;
  float height;

  float rotation;

  void (*update)(int index, float dt);
};

void draw(struct Sprite sprite);

#endif
