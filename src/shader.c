#include <stdio.h>
#include <glad/glad.h>

#include <astroids/error.h>

// Pre-define error functions
static void checkCompileErrors(int shader);
static void checkLinkErrors(int program);

unsigned int generateShaders(const char *vertexShaderSource, const char *fragmentShaderSource) {

  // Compile shaders
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader);

  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader);

  // Create program
  int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  checkLinkErrors(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

static void checkCompileErrors(int shader) {
  int success;
  char log[1000];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1000, NULL, log);
    error("%s", log);
  }
}

static void checkLinkErrors(int program) {
  int success;
  char log[1000];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1000, NULL, log);
    error("%s", log);
  }
}
