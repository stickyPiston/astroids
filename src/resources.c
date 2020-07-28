#include <astroids/texture.h>
#include <astroids/resources.h>
#include <astroids/error.h>

#include <stdio.h>
#include <stdlib.h>

static struct Texture textureMap[] = {
  {"player", "src/textures/player.png", 0}
};

void initResources() {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    char resolvedPath[1000];
    char *result = realpath(textureMap[i].path, resolvedPath);
    if (result != NULL) {
      int id = loadTexture(resolvedPath);
      textureMap[i].id = id;
    } else {
      error("The path to the resource is not valid! Evaluating %s", textureMap[i].path);
    }
  }
}

unsigned int getResource(char *name) {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    if (textureMap[i].name == name) {
      return textureMap[i].id;
    }
  }

  error("Resource requested that doesn't exist within the textureMap!");
  return 0; 
}
