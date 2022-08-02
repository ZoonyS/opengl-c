#include "core/scene.h"

Scene *init_scene()
{
  Scene *scene = (Scene *) malloc(sizeof(Scene));
  if (!scene)
  {
    printf("Error: Could not allocate memory for scene.\n");
    return NULL;
  }
  memset(scene, 0, sizeof(Scene));

  GLuint shader_program = loadShaderProgramFromFile((GLchar *) "res/shaders/simple.vs.glsl", (GLchar *) "res/shaders/simple.fs.glsl");
  if (shader_program == 0)
  {
    free_scene(scene);
    printf("Error: Could not load shader program.\n");
    return NULL;
  }
  
  Object *object;
  if (!(init_object()))
  {
    free_scene(scene);
    printf("Error: Could not load object\n");
    return NULL;
  }

  scene->shader_program = shader_program;
  scene->object = object;

  return scene;
}

void render_scene(GLFWwindow *window, Scene *scene)
{
 while (!glfwWindowShouldClose(window))
  {
    // inputs
    processInput(window);

    // color
    float time = glfwGetTime() * 2;
    GLfloat r, g, b;
    
    getRgbRainbow(&r, &g, &b, time);

    // rendering
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // int vertexColorLocation = glGetUniformLocation(scene->shader_program, "ourColor");
    // Object *object = scene->object;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->object->TEX);

    glUseProgram(scene->shader_program);
    glBindVertexArray(scene->object->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

 glfwTerminate();
}

void free_scene(Scene *scene)
{
  if (scene == NULL)
    return;

  if (scene->shader_program)
    glDeleteProgram(scene->shader_program);

  //if (scene->view)
  //  free(scene->view);

  if (scene->object)
  {
    if (scene->object->VAO)
      glDeleteVertexArrays(1, &scene->object->VAO);
    if (scene->object->VBO)
      glDeleteBuffers(1, &scene->object->VBO);
    if (scene->object->EBO)
      glDeleteBuffers(1, &scene->object->EBO);
    //if (scene->object->texture)
    //  glDeleteTextures(1, &scene->object->texture);
    free(scene->object);
  }

   free(scene);
}

void getRgbRainbow(GLfloat *r, GLfloat *g, GLfloat *b, GLfloat time)
{
  *r = sin(time) * 0.5 + 0.5;
  *g = sin(time * 0.5) * 0.5 + 0.5;
  *b = sin(time * 0.25) * 0.5 + 0.5;
}

