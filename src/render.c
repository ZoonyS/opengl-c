#include "core/common.h"

void render(GLuint shaderProgram, GLuint vertexArrayObject) {
    // const char *vertexShaderSource = "#version 330 core\n"
    //     "layout (location = 0) in vec3 aPos;\n"
    //     "void main()\n"
    //     "{\n"
    //     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //     "}\0";

    // const char *fragmentShaderSource = "#version 330 core\n"
    //     "out vec4 FragColor;\n"
    //     "void main()\n"
    //     "{\n"
    //     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //     "}\0";
    
    // // for debugging at compile
    // int  success;
    // char infoLog[512];

    // // vertex shader
    // unsigned int vertexShader;
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);
    
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if(!success)
    // {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     printf(infoLog);
    // }

    // // fragment shader
    // unsigned int fragmentShader;
    // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);

    // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // if(!success)
    // {
    //     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //     printf(infoLog);
    // }

    // // shader program
    // unsigned int shaderProgram;
    // shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram); // link compiled shaders to program object
    
    // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if(!success) {
    //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //     printf(infoLog);
    // }

    // // delete linked shader objects
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);  

    // // vertex data
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f
    // };
    
    // // vertex buffer
    // unsigned int vertexBufferObject;
    // glGenBuffers(1, &vertexBufferObject);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // linking vertex attributes
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // vertex array object
    // unsigned int vertexArrayObject;
    // glGenVertexArrays(1, &vertexArrayObject);  
    // glBindVertexArray(vertexArrayObject);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject); // copy our vertices array in a buffer
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // set our vertex attributes pointers
    // glEnableVertexAttribArray(0);  

    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // // delete already linked shader objects
    // glDeleteVertexArrays(1, &vertexArrayObject);
    // glDeleteBuffers(1, &vertexBufferObject);
    // glDeleteProgram(shaderProgram);

    // // background colour
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}