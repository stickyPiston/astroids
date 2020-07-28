#include <astroids/texture.h>
#include <astroids/resources.h>
#include <astroids/error.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Texture textureMap[] = {
  {"player", "src/textures/player.png", 0}
};

void initResources() {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    int id = loadTexture(textureMap[i].path);
    textureMap[i].id = id;
  }
}

unsigned int getResource(char *name) {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    if (strcmp(textureMap[i].name, name) == 0) {
      return textureMap[i].id;
    }
  }

  error("Resource requested that doesn't exist within the textureMap!");
  return 0; 
}
