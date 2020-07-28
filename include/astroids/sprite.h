#ifndef SPRITE_H
#define SPRITE_H

#include <astroids/quad.h>

struct Sprite {
  struct Shape shape;
  unsigned int texture;
  unsigned int program;
};

void draw(struct Sprite sprite);

#endif
