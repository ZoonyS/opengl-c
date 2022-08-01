#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include "math/vector.h"

typedef struct {
  float *texture_coords;
  float *vertices; 
  unsigned int *indices;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLuint TEX;
} Object;

Object* init_object();
void link_vertex_attributes();

#endif // !OBJECT_H
