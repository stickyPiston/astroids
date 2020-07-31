#ifndef RESOURCES_H
#define RESOURCES_H

#include <astroids/quad.h>

struct Texture {
  char *name;
  char *path;
  unsigned int id;
};

void initResources();

struct Shape getShape();

unsigned int getShader();

unsigned int getTexture(char *name);

#endif
