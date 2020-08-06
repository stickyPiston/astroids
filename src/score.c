#include <astroids/sprite.h>
#include <astroids/resources.h>
#include <astroids/score.h>

#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int score = 0;


struct Sprite *displayScore() {
  int copy = score;

  int numDigits = copy <= 1 ? 1 : ceil(log10(copy));

  struct Sprite *sprites = NULL;
  int *digits = NULL;

  while (copy > 0) {
    int digit = copy % 10;

    arrins(digits, 0, digit);

    copy /= 10;
  }

  float x = -0.8;
  for (int i = 0; i < arrlen(digits); i++) {
    char digitString[3];
    strcpy(digitString, "");
    sprintf(digitString, "%d", digits[i]);

    struct Sprite sprite = {
      getShape(),
      getTexture(digitString),
      getShader(),
      x,
      0.85,
      0.06,
      0.06,
      0,
      NULL
    }; 

    arrput(sprites, sprite);
    x += 0.06;
  }

  return sprites;
}
