#include <stdlib.h>
#include <stdio.h>

#include <astroids/error.h>

char *readFile(char *path) {
  char *buffer = 0;
  long length;
  FILE *f = fopen(path, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);

    if (buffer) {
      fread(buffer, 1, length, f);
    }

    buffer[length] = '\0';

    fclose(f);
  } else {
    error("Couldn't read file %s", path);
  }

  return buffer;
}
