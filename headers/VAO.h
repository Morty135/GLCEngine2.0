#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"VBO.h"

class VAO
{
public:
    unsigned int ID;

    VAO();

    void Bind();
    void VAO::LinkAttrib(VBO& VBO, unsigned int layout);
    void Unbind();
    void Delete();
};


#endif