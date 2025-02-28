#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <cglm/cglm.h>

// Setup cube VAO, VBO, and EBO
void setupCube(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO);

//sets a block 
void setBlock(bool* blockGrid, int x, int y, int z, int width, int height, int depth, bool value);

//Check if block is avalable
bool getBlock(bool* blockGrid, int x, int y, int z, int width, int height, int depth);

// Create floor grid of cubes
void createFloorGrid(vec3 positions[], int width, int depth);

//create floor grid of cube with perilian noise
void createTerrainGrid(vec3 positions[], int width, int depth, int seed);

#endif // CUBE_H