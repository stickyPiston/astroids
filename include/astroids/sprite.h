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
};

void draw(struct Sprite sprite);

#endif
