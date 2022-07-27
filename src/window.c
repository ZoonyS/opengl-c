#include "core/common.h"

int initWindow(unsigned int width, unsigned int height, const char* title) {
  initGLFW();

  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL)
  {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    return -1;
  }

  // REFACTOR THIS !!!!!

  // MAKE THESE SEPERATE FILES -------------------------
  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

  const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
  // --------------------------------------------------

  // for debugging at compile
  int  success;
  char infoLog[512];

  // vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf(infoLog);
  }

  // fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf(infoLog);
  }

  // shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram); // link compiled shaders to program object
  
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf(infoLog);
  }

  // delete linked shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);  

  // vertex data
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f,  // right
    0.0f, 0.5f, 0.0f    // top
  };
  
  // vertex buffer object
  unsigned int vertexBufferObject;
  glGenBuffers(1, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // linking vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // vertex array object
  unsigned int vertexArrayObject;
  glGenVertexArrays(1, &vertexArrayObject);  
  glBindVertexArray(vertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject); // copy our vertices array in a buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // set our vertex attributes pointers
  glEnableVertexAttribArray(0);  

  while (!glfwWindowShouldClose(window))
  {
    // inputs
    processInput(window);

    GLfloat r, g, b;
    getRgbRainbow(&r, &g, &b);

    // rendering
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render(shaderProgram, vertexArrayObject);

    // swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // de-allocate resources
  glDeleteVertexArrays(1, &vertexArrayObject);
  glDeleteBuffers(1, &vertexBufferObject);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

void getRgbRainbow(GLfloat *r, GLfloat *g, GLfloat *b)
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  long long milli = (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
  long long nmilli = milli * 0.01;

  *r = sin(nmilli) * 0.5 + 0.5;
  *g = sin(nmilli * 0.5) * 0.5 + 0.5;
  *b = sin(nmilli * 0.25) * 0.5 + 0.5;
}

void initGLFW() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
    #endif
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}
