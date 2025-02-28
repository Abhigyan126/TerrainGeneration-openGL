#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window size
extern const int WIDTH;
extern const int HEIGHT;

// Initialize GLFW and create window
GLFWwindow* initializeWindow(void);

#endif // WINDOW_H