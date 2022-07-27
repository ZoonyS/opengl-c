#include "core/common.h"

void render(GLuint shaderProgram, GLuint vertexArrayObject) {
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}