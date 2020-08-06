#include <stb/stb_ds.h>
#include <stb/stb.h>

#include <astroids/resources.h>
#include <astroids/sprite.h>

#include <math.h>

struct {
  struct Sprite player;
  struct Sprite *bullets;
  struct Sprite *astroids;
} entities;
int score;


static void bullet_update(int index, float dt) {
  float speed = 2;

  // Transform a first, because openGL messes up the rotations for whatever reason.
  float a = (entities.bullets[index].rotation - 1.57) + M_PI;

  entities.bullets[index].x += speed * cos(a) * dt;
  entities.bullets[index].y += speed * sin(a) * dt;

  struct Sprite bullet = entities.bullets[index];
  int hit = 0;
  for (int i = 0; i < arrlen(entities.astroids); i++) {
    struct Sprite astroid = entities.astroids[i];
    if (
         bullet.x + bullet.width >= astroid.x
      && bullet.x <= astroid.x + 0.9 * astroid.width
      && bullet.y + bullet.height >= astroid.y
      && bullet.y <= astroid.y + 0.9 * astroid.height
    ) {
      hit = 1;
      arrdel(entities.astroids, i);
      arrdel(entities.bullets, index);
      score += 10;
    }
  } 

    if (
         !hit
      && (
         entities.bullets[index].x > 1
      || entities.bullets[index].x < -1
      || entities.bullets[index].y > 1
      || entities.bullets[index].y < -1
      )
    ) {
      arrdel(entities.bullets, index);
    }
}

void makeBullet() {
  struct Shape quad = getShape();
  unsigned int shader = getShader();
  unsigned int texture = getTexture("player");

  struct Sprite sprite = {
    quad,                     // shape
    texture,                  // texture
    shader,                   // shaders
    entities.player.x,        // x 
    entities.player.y,        // y
    0.03,                     // width
    0.03,                     // height
    entities.player.rotation, // rotation
    bullet_update             // update
  };

  arrput(entities.bullets, sprite);
}
