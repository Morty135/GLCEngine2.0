#ifndef GLCTEXTURE_H
#define GLCTEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <iostream>

#include <GLCShader.h>



struct GLCTextureStruct {
    unsigned int id;
    std::string type;
    std::string path;
};



class GLCTexture
{
public:
    GLCTexture(GLCTextureStruct TextureStruct);

    void texUnit(GLCShader& shader, const char* uniform, unsigned int unit);

	void Bind();

	void Unbind();

	void Delete();
};



#endif