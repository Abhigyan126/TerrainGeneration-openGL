#include "texture.h"
#include "stb_image.h"
#include <stdio.h>

unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Flip image vertically so texture coordinates match OpenGL's expectations
    stbi_set_flip_vertically_on_load(1);
    
    // Load image data
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    
    if (data) {
        printf("Texture loaded successfully: %dx%d with %d channels\n", width, height, nrChannels);
        
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;
            
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
        return textureID;
    } else {
        printf("Failed to load texture at path: %s\n", path);
        stbi_image_free(data);
        return 0;
    }
}