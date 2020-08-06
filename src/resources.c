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
  {"player", SRC_DIR"/textures/player.png", 0},
  {"start", SRC_DIR"/textures/start.png", 0},
  {"title", SRC_DIR"/textures/title.png", 0},
  {"score", SRC_DIR"/textures/score.png", 0},
  {"lives", SRC_DIR"/textures/lives.png", 0},
  {"astroid1", SRC_DIR"/textures/astroid_1.png", 0},
  {"astroid2", SRC_DIR"/textures/astroid_2.png", 0},
  {"astroid3", SRC_DIR"/textures/astroid_3.png", 0},
  {"astroid4", SRC_DIR"/textures/astroid_4.png", 0},
  {"astroid5", SRC_DIR"/textures/astroid_5.png", 0},
  {"0", SRC_DIR"/textures/digits/0.png", 0},
  {"1", SRC_DIR"/textures/digits/1.png", 0},
  {"2", SRC_DIR"/textures/digits/2.png", 0},
  {"3", SRC_DIR"/textures/digits/3.png", 0},
  {"4", SRC_DIR"/textures/digits/4.png", 0},
  {"5", SRC_DIR"/textures/digits/5.png", 0},
  {"6", SRC_DIR"/textures/digits/6.png", 0},
  {"7", SRC_DIR"/textures/digits/7.png", 0},
  {"8", SRC_DIR"/textures/digits/8.png", 0},
  {"9", SRC_DIR"/textures/digits/9.png", 0}
};

static unsigned int shaderProgram = 0;

static struct Shape quad = {0, 0};

void initResources() {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    int id = loadTexture(textureMap[i].path);
    textureMap[i].id = id;
  }

  char *vertexShaderSource = readFile(SRC_DIR"/shaders/vertex.glsl");
  char *fragmentShaderSource = readFile(SRC_DIR"/shaders/fragment.glsl");
  shaderProgram = generateShaders(vertexShaderSource, fragmentShaderSource);
  quad = generateQuad();
}

struct Shape getShape() {
  if (quad.VAO == 0 && quad.EBO == 0) error("The quad is 0, did initResources run?\n");
  return quad;
}

unsigned int getShader() {
  if (shaderProgram == 0) error("The shader program is 0, did initResources() run?\n");
  return shaderProgram;
}

unsigned int getTexture(char *name) {
  int mapSize = sizeof(textureMap) / sizeof(struct Texture);

  for (int i = 0; i < mapSize; i++) {
    if (strcmp(textureMap[i].name, name) == 0) {
      return textureMap[i].id;
    }
  }

  error("Resource requested that doesn't exist within the textureMap! Evaluating %s\n", name);
  return 0; 
}
