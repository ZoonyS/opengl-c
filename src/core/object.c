#include "core/object.h"

Object *init_object()
{
  // vertex data
  float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f  // top left 
  };

  unsigned int indices[] = {
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };
  
  // vertex buffer object
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // copy our vertices array in a buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // vertex array object
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);  
  glBindVertexArray(VAO);

  // elemental buffer object
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // render the triangles from index buffer

  // linking vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  link_vertex_attributes();

  Object *object = (Object *) malloc(sizeof(Object));
  if (!object)
  {
    printf("Error: Could not allocate memory for object.\n");
    return NULL;
  }

  object->vertices = vertices;
  object->indices = indices;
  object->VBO = VBO;
  object->VAO = VAO;
  object->EBO = EBO;

  link_vertex_attributes();

  return object;
}

void link_vertex_attributes()
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
