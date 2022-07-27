#ifndef WINDOW_H
#define WINDOW_H

int initWindow(unsigned int, unsigned int, const char *);
extern void render(GLuint, GLuint);
extern void processInput(GLFWwindow *);
void getRgbRainbow(GLfloat *, GLfloat *, GLfloat *, float);
void initGLFW();
void framebuffer_size_callback(GLFWwindow *, int, int);

#endif