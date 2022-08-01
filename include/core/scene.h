#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/shader_loader.h"
#include "core/object.h"
#include "core/input.h"

typedef struct {
  GLuint shader_program;
  //View *view;
  Object *object;   
} Scene;

Scene* init_scene();
void render_scene(GLFWwindow *window, Scene *scene);
void free_scene();
void getRgbRainbow(GLfloat *r, GLfloat *g, GLfloat *b, GLfloat time);

#endif // !SCENE_H
