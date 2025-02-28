#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdbool.h>

// Initialize camera
void initializeCamera(void);

// Set delta time 
void setDeltaTime(float dt);

// Process keyboard input
void processInput(GLFWwindow *window);

// Mouse callback function
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Scroll callback for zoom
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Update view and projection matrices
void updateCameraMatrices(mat4 view, mat4 projection);

#endif // CAMERA_H