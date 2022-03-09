#include <astroids/sprite.h>
#include <astroids/resources.h>

#include <string.h>
#include <stdio.h>

extern int lives;

struct Sprite displayLives() {
  char livesString[3];
  strcpy(livesString, "");
  sprintf(livesString, "%d", lives);

  struct Sprite sprite = {
    getShape(),
    getTexture(livesString),
    getShader(),
    -0.8,
    0.95,
    0.06,
    0.06,
    0,
    NULL
  }; 

  return sprite;
}
