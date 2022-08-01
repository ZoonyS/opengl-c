#include "core/object.h"

Object *init_object()
{
  // vertex data
  float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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

  // link attributes
  link_vertex_attributes();

  // texture
  unsigned int TEX;
  glGenTextures(1, &TEX);
  glBindTexture(GL_TEXTURE_1D, TEX);

  // wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load image, create texture, generate mipmaps
  int width, height, nr_channels;
  stbi_set_flip_vertically_on_load(0); // flip loaded textures on y axis

  unsigned char *data = stbi_load("res/images/DVD.png", &width, &height, &nr_channels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("error loading texture\n");
  }
  stbi_image_free(data);

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
  object->TEX = TEX;

  return object;
}

void link_vertex_attributes()
{
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}
