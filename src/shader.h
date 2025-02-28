#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

// Create and return shader program
unsigned int createShaderProgram(void);

// Check for shader compilation and linking errors
void checkCompileErrors(GLuint shader, char *type);

#endif // SHADER_H