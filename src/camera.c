#include "camera.h"
#include "window.h"
#include <math.h>

// Camera variables
static vec3 cameraPos = {0.0f, 1.0f, 3.0f};
static vec3 cameraFront = {0.0f, 0.0f, -1.0f};
static vec3 cameraUp = {0.0f, 1.0f, 0.0f};
static float yaw = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in looking to the right
static float pitch = 0.0f;
static float fov = 45.0f;
static bool firstMouse = true;
static float lastX;
static float lastY;

// Timing
static float deltaTime = 0.0f;  // Time between current frame and last frame

void initializeCamera(void) {
    cameraPos[0] = 0.0f;
    cameraPos[1] = 1.0f;  // Eye level above the floor
    cameraPos[2] = 5.0f;  // Start a bit back from the floor
    
    lastX = WIDTH / 2.0;
    lastY = HEIGHT / 2.0;
}

void setDeltaTime(float dt) {
    deltaTime = dt;
}

void processInput(GLFWwindow *window) {
    float cameraSpeed = 30.0f * deltaTime; //change to impact movement spped
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // Forward movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3 step;
        glm_vec3_scale(cameraFront, cameraSpeed, step);
        glm_vec3_add(cameraPos, step, cameraPos);
    }
    
    // Backward movement
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3 step;
        glm_vec3_scale(cameraFront, cameraSpeed, step);
        glm_vec3_sub(cameraPos, step, cameraPos);
    }
    
    // Left movement
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 cross;
        glm_vec3_cross(cameraFront, cameraUp, cross);
        glm_vec3_normalize(cross);
        vec3 step;
        glm_vec3_scale(cross, cameraSpeed, step);
        glm_vec3_sub(cameraPos, step, cameraPos);
    }
    
    // Right movement
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 cross;
        glm_vec3_cross(cameraFront, cameraUp, cross);
        glm_vec3_normalize(cross);
        vec3 step;
        glm_vec3_scale(cross, cameraSpeed, step);
        glm_vec3_add(cameraPos, step, cameraPos);
    }
    
    // Up movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos[1] += cameraSpeed;
    }
    
    // Down movement
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos[1] -= cameraSpeed;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    vec3 front;
    front[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    front[1] = sin(glm_rad(pitch));
    front[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_vec3_normalize_to(front, cameraFront);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void updateCameraMatrices(mat4 view, mat4 projection) {
    // Update view matrix
    vec3 cameraTarget;
    glm_vec3_add(cameraPos, cameraFront, cameraTarget);
    glm_lookat(cameraPos, cameraTarget, cameraUp, view);
    
    // Update projection matrix
    glm_perspective(glm_rad(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f, projection);
}