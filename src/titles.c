#include <astroids/sprite.h>
#include <astroids/resources.h>

#include <stdlib.h>

static struct Sprite titleCache;
static struct Sprite pressStartCache;
static struct Sprite scoreCache;
static struct Sprite livesCache;

struct Sprite getLivesTitle() {
  if (livesCache.width == 0) {
    struct Sprite sprite = {
      getShape(),
      getTexture("lives"),
      getShader(),
      -0.9,
      0.95,
      0.1,
      0.05,
      0,
      NULL
    };

    livesCache = sprite;
  }

  return livesCache;
}

struct Sprite getScoreTitle() {
  if (scoreCache.width == 0) {
    struct Sprite sprite = {
      getShape(),
      getTexture("score"),
      getShader(),
      -0.9,
      0.85,
      0.1,
      0.05,
      0,
      NULL
    };
    
    scoreCache = sprite;
  }

  return scoreCache;
}

struct Sprite getTitle() {
  if (titleCache.width == 0) {
    struct Sprite sprite = {
      getShape(),
      getTexture("title"),
      getShader(),
      0,
      0.3,
      0.8,
      0.3,
      0,
      NULL
    };

    titleCache = sprite;
  }

  return titleCache;
}

struct Sprite getPressStart() {
  if (pressStartCache.width == 0) {
    struct Sprite sprite = {
      getShape(),
      getTexture("start"),
      getShader(),
      0,
      -0.4,
      0.6,
      0.1,
      0,
      NULL
    };

    pressStartCache = sprite;
  }

  return pressStartCache;
}
