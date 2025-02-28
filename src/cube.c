#include "cube.h"
#include <math.h>

// Function to create a single cube at specified grid coordinates
void createCube(float* vertices, unsigned int* indices, int vertexOffset, int indexOffset, int x, int y, int z) {
    // Size of each cube
    const float cubeSize = 1.0f;
    
    // Calculate world position based on grid coordinates
    float worldX = x * cubeSize;
    float worldY = y * cubeSize;
    float worldZ = z * cubeSize;
    
    // Define cube vertices with position and texture coordinates
    float cubeVertices[] = {
        // positions (x, y, z)       // texture coords (u, v)
        // Front face
        0.0f, 0.0f, cubeSize,        0.0f, 0.0f,
        cubeSize, 0.0f, cubeSize,    1.0f, 0.0f,
        cubeSize, cubeSize, cubeSize, 1.0f, 1.0f,
        0.0f, cubeSize, cubeSize,    0.0f, 1.0f,
        
        // Back face
        0.0f, 0.0f, 0.0f,            1.0f, 0.0f,
        cubeSize, 0.0f, 0.0f,        0.0f, 0.0f,
        cubeSize, cubeSize, 0.0f,    0.0f, 1.0f,
        0.0f, cubeSize, 0.0f,        1.0f, 1.0f,
        
        // Top face
        0.0f, cubeSize, cubeSize,    0.0f, 0.0f,
        cubeSize, cubeSize, cubeSize, 1.0f, 0.0f,
        cubeSize, cubeSize, 0.0f,    1.0f, 1.0f,
        0.0f, cubeSize, 0.0f,        0.0f, 1.0f,
        
        // Bottom face
        0.0f, 0.0f, cubeSize,        0.0f, 1.0f,
        cubeSize, 0.0f, cubeSize,    1.0f, 1.0f,
        cubeSize, 0.0f, 0.0f,        1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,            0.0f, 0.0f,
        
        // Right face
        cubeSize, 0.0f, cubeSize,    0.0f, 0.0f,
        cubeSize, cubeSize, cubeSize, 0.0f, 1.0f,
        cubeSize, cubeSize, 0.0f,    1.0f, 1.0f,
        cubeSize, 0.0f, 0.0f,        1.0f, 0.0f,
        
        // Left face
        0.0f, 0.0f, cubeSize,        1.0f, 0.0f,
        0.0f, cubeSize, cubeSize,    1.0f, 1.0f,
        0.0f, cubeSize, 0.0f,        0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,            0.0f, 0.0f
    };

    // Add world position offset to each vertex
    for (int i = 0; i < 24; i++) {
        int baseIndex = i * 5;
        vertices[vertexOffset + baseIndex] = cubeVertices[baseIndex] + worldX;
        vertices[vertexOffset + baseIndex + 1] = cubeVertices[baseIndex + 1] + worldY;
        vertices[vertexOffset + baseIndex + 2] = cubeVertices[baseIndex + 2] + worldZ;
        vertices[vertexOffset + baseIndex + 3] = cubeVertices[baseIndex + 3];
        vertices[vertexOffset + baseIndex + 4] = cubeVertices[baseIndex + 4];
    }

    // Define indices with offset
    for (int i = 0; i < 36; i++) {
        int vertIdx = i / 6 * 4 + i % 6;
        if (i % 6 == 3) vertIdx = i / 6 * 4 + 0;
        if (i % 6 == 4) vertIdx = i / 6 * 4 + 2;
        if (i % 6 == 5) vertIdx = i / 6 * 4 + 0;
        indices[indexOffset + i] = vertIdx + vertexOffset / 5;
    }
}

// Function to setup a single cube
void setupCube(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO) {
    // Define cube vertices with correct texture coordinates for all faces
    float vertices[] = {
        // positions          // texture coords
        // Front face
        0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,     0.0f, 1.0f,
        
        // Back face
        0.0f, 0.0f, 0.0f,     1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
        
        // Top face
        0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,     1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
        
        // Bottom face
        0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        
        // Right face
        1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
        
        // Left face
        0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,     1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,     0.0f, 0.0f
    };

    // Index data for all 6 faces (2 triangles per face)
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,       // Front face
        4, 5, 6, 6, 7, 4,       // Back face
        8, 9, 10, 10, 11, 8,    // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Right face
        20, 21, 22, 22, 23, 20  // Left face
    };

    // Create and bind VAO, VBO, and EBO
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(*VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

// Create a grid of cubes with integer coordinates
void createBlockGrid(unsigned int* gridVAO, unsigned int* gridVBO, unsigned int* gridEBO, int width, int height, int depth) {
    int totalCubes = width * height * depth;
    int verticesPerCube = 24 * 5; // 24 vertices with 5 attributes each
    int indicesPerCube = 36;      // 6 faces * 2 triangles * 3 vertices
    
    float* vertices = (float*)malloc(totalCubes * verticesPerCube * sizeof(float));
    unsigned int* indices = (unsigned int*)malloc(totalCubes * indicesPerCube * sizeof(unsigned int));
    
    int vertexOffset = 0;
    int indexOffset = 0;
    
    // Generate cubes for the grid
    for (int y = 0; y < height; y++) {
        for (int z = 0; z < depth; z++) {
            for (int x = 0; x < width; x++) {
                // Create cube at integer coordinates
                createCube(vertices, indices, vertexOffset, indexOffset, x, y, z);
                
                vertexOffset += verticesPerCube;
                indexOffset += indicesPerCube;
            }
        }
    }
    
    // Create and bind VAO, VBO, and EBO
    glGenVertexArrays(1, gridVAO);
    glGenBuffers(1, gridVBO);
    glGenBuffers(1, gridEBO);
    
    glBindVertexArray(*gridVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, *gridVBO);
    glBufferData(GL_ARRAY_BUFFER, totalCubes * verticesPerCube * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *gridEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalCubes * indicesPerCube * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Free allocated memory
    free(vertices);
    free(indices);
}

void createFloorGrid(vec3 positions[], int width, int depth) {
    int index = 0;
    
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            // Use integer coordinates directly
            positions[index][0] = (float)x;
            positions[index][1] = 0.0f;
            positions[index][2] = (float)z;
            
            index++;
        }
    }
}

// Helper function to set or remove a block at a specific grid position
void setBlock(bool* blockGrid, int x, int y, int z, int width, int height, int depth, bool value) {
    if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth) {
        blockGrid[x + width * (y + height * z)] = value;
    }
}

// Helper function to check if a block exists at a specific grid position
bool getBlock(bool* blockGrid, int x, int y, int z, int width, int height, int depth) {
    if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth) {
        return blockGrid[x + width * (y + height * z)];
    }
    return false;
}

// Pseudo-random_ number generator with seed
float random_(int x, int y, int seed) {
    int n = x + y * 57 + seed * 131;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

// Simple smoothing function for noise
float smoothNoise(int x, int y, int seed) {
    float corners = (random_(x-1, y-1, seed) + random_(x+1, y-1, seed) + 
                     random_(x-1, y+1, seed) + random_(x+1, y+1, seed)) / 16.0f;
    float sides = (random_(x-1, y, seed) + random_(x+1, y, seed) + 
                   random_(x, y-1, seed) + random_(x, y+1, seed)) / 8.0f;
    float center = random_(x, y, seed) / 4.0f;
    return corners + sides + center;
}

// Interpolated noise for smoother terrain
float interpolatedNoise(float x, float y, int seed) {
    int intX = (int)x;
    float fracX = x - intX;
    
    int intY = (int)y;
    float fracY = y - intY;
    
    float v1 = smoothNoise(intX, intY, seed);
    float v2 = smoothNoise(intX + 1, intY, seed);
    float v3 = smoothNoise(intX, intY + 1, seed);
    float v4 = smoothNoise(intX + 1, intY + 1, seed);
    
    // Cosine interpolation for smoother blending
    float i1 = v1 * (1 - fracX) + v2 * fracX;
    float i2 = v3 * (1 - fracX) + v4 * fracX;
    
    return i1 * (1 - fracY) + i2 * fracY;
}

// Generate perlin-like noise at a given point
float perlinNoise(float x, float y, int seed, int octaves) {
    float total = 0.0f;
    float persistence = 0.5f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float maxValue = 0.0f;
    
    for (int i = 0; i < octaves; i++) {
        total += interpolatedNoise(x * frequency, y * frequency, seed) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }
    
    return total / maxValue;
}

// Main terrain generation function
// Modified terrain generation function with discrete block heights
void createTerrainGrid(vec3 positions[], int width, int depth, int seed) {
    int index = 0;
    
    int maxHeight = 30;       // Maximum height of terrain in blocks
    int baseHeight = 3;       // Minimum base height to avoid holes
    int octaves = 4;          // Detail level of the noise
    
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            // Get base position
            positions[index][0] = (float)x;
            
            // Generate height using Perlin noise
            float noiseValue = perlinNoise((float)x / 20.0f, (float)z / 20.0f, seed, octaves);
            
            // Convert to discrete block height by flooring to integer
            // Scale noise to be between 0 and maxHeight, then add baseHeight
            int blockHeight = baseHeight + (int)floorf(noiseValue * maxHeight);
            
            positions[index][1] = (float)blockHeight;
            positions[index][2] = (float)z;
            
            index++;
        }
    }
}