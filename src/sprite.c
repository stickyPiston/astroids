#include <glad/glad.h>

#include <astroids/sprite.h>

void draw(struct Sprite sprite) {

  glUseProgram(sprite.program);
  glBindTexture(GL_TEXTURE_2D, sprite.texture);
  glBindVertexArray(sprite.shape.VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.shape.EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
