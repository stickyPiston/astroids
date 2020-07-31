#include <stdlib.h>
#include <stdio.h>

#include <astroids/error.h>

#ifdef _WIN32
  #include <windows.h>
#endif

char *readFile(char *path) {
  char resolvedPath[1000];
  
  #ifdef _WIN32
    GetFullPathName(path, 1000, resolvedPath, NULL);
  #else
    realpath(path, resolvedPath);
  #endif

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
