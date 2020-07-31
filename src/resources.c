#include <astroids/texture.h>
#include <astroids/resources.h>
#include <astroids/error.h>
#include <astroids/shader.h>
#include <astroids/quad.h>
#include <astroids/file.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Texture textureMap[] = {
  {"player", "src/textures/player.png", 0}
};

static unsigned int shaderProgram = 0;

static struct Shape quad = {0, 0};

void initResources() {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    int id = loadTexture(textureMap[i].path);
    textureMap[i].id = id;
  }

  // FIXME: Generate paths on compilation to ensure they're always correct.
  char *vertexShaderSource = readFile("src/shaders/vertex.glsl");
  char *fragmentShaderSource = readFile("src/shaders/fragment.glsl");
  shaderProgram = generateShaders(vertexShaderSource, fragmentShaderSource);
  quad = generateQuad();
}

struct Shape getShape() {
  if (quad.VAO == 0 && quad.EBO == 0) error("The quad is 0, did initResources run?");
  return quad;
}

unsigned int getShader() {
  if (shaderProgram == 0) error("The shader program is 0, did initResources() run?");
  return shaderProgram;
}

unsigned int getTexture(char *name) {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    if (strcmp(textureMap[i].name, name) == 0) {
      return textureMap[i].id;
    }
  }

  error("Resource requested that doesn't exist within the textureMap!");
  return 0; 
}
