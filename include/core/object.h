#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
  float *vertices; 
  unsigned int *indices;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
} Object;

Object* init_object();
void link_vertex_attributes();

#endif // !OBJECT_H
