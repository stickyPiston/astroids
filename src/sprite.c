#include <glad/glad.h>

#include <astroids/sprite.h>

#include <math.h>

void draw(struct Sprite sprite) {

  float sx = sprite.width;
  float sy = sprite.height;
  float sz = 1.0;

  float tx = sprite.x;
  float ty = sprite.y;
  float tz = 0.0;

  float a = sprite.rotation;

  float transformMatrix[] = {
    sx * cos(a), -sx * sin(a), 0 , tx,
    sy * sin(a),  sy * cos(a), 0 , ty,
    0          ,  0          , sz, tz,
    0          ,  0          , 0 , 1
  };

  unsigned int transformLoc = glGetUniformLocation(sprite.program, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_TRUE, transformMatrix);

  glUseProgram(sprite.program);
  glBindTexture(GL_TEXTURE_2D, sprite.texture);
  glBindVertexArray(sprite.shape.VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.shape.EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
