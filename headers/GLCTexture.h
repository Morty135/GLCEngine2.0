#ifndef GLCTEXTURE_H
#define GLCTEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>


class GLCTexture
{
public:
    unsigned int ID;
    const char* type;
	unsigned int unit;


    GLCTexture(const char* textureSource, const char* texType, unsigned int slot);

    void Bind();
};



#endif