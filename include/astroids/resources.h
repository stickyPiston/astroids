#ifndef RESOURCES_H
#define RESOURCES_H

struct Texture {
  char *name;
  char *path;
  unsigned int id;
};

void initResources();

unsigned int getResource(char *name);

#endif
