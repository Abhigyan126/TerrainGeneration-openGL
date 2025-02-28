#include "window.h"
#include <stdio.h>

// Window size
const int WIDTH = 800;
const int HEIGHT = 600;

GLFWwindow* initializeWindow(void) {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Navigable Cube Floor", NULL, NULL);
    if (!window) {
        printf("Failed to create window\n");
        glfwTerminate();
        return NULL;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        glfwTerminate();
        return NULL;
    }
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    return window;
}