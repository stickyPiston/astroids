#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <astroids/quad.h>
#include <astroids/file.h>
#include <astroids/shader.h>
#include <astroids/sprite.h>
#include <astroids/resources.h>

struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;

void makePlayer() {
  struct Shape quad = getShape();
  unsigned int shader = getShader();
  unsigned int texture = getTexture("player");

  struct Sprite sprite = {
    quad,       // shape
    texture,    // texture
    shader,     // shaders
    0.5,        // x 
    0.5,        // y
    0.03,       // width
    0.05,       // height
    3.14,       // rotation
    NULL        // Update function
  };
  entities.player = sprite;
}
