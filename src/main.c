#include "window.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include <stdio.h>

// Define the dimensions of our floor grid
const int GRID_WIDTH = 500;  // 10 cubes along X axis
const int GRID_DEPTH = 100;  // 10 cubes along Z axis

int main() {
    // Initialize window and OpenGL context
    GLFWwindow* window = initializeWindow();
    if (!window) {
        return -1;
    }
    
    // Set up camera
    initializeCamera();

    // Set up input callbacks
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Capture cursor
    
    // Create and compile shaders
    unsigned int shaderProgram = createShaderProgram();
    
    // Create cube VAO, VBO, EBO
    unsigned int VAO, VBO, EBO;
    setupCube(&VAO, &VBO, &EBO);
    
    // Load texture
    unsigned int texture = loadTexture("texture.jpg");
    if (texture == 0) {
        printf("Failed to load texture. Make sure texture.jpg is in the same directory!\n");
    }

    // Get uniform locations
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Set initial clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Generate positions for floor grid
    vec3 cubePositions[GRID_WIDTH * GRID_DEPTH];
    createTerrainGrid(cubePositions, GRID_WIDTH, GRID_DEPTH, 123127);

    // Render loop
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        setDeltaTime(currentFrame - lastFrame);
        lastFrame = currentFrame;
        
        // Process input
        processInput(window);
        
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        glUseProgram(shaderProgram);
        
        // Set view/projection matrices based on camera position
        mat4 view;
        mat4 projection;
        updateCameraMatrices(view, projection);
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float*)projection);
        
        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        
        // Draw each cube in the floor grid
        for (int i = 0; i < GRID_WIDTH * GRID_DEPTH; i++) {
            mat4 model;
            glm_mat4_identity(model);
            glm_translate(model, cubePositions[i]);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);

    glfwTerminate();
    return 0;
}