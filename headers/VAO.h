#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include <VBO.h>

class VAO
{
public:
    unsigned int ID;

    VAO();

    void LinkAttrib(VBO &VBO, unsigned int layout, unsigned int lenght, GLenum type, GLsizeiptr stride, void* offset);

    void Bind();
    
    void Unbind();

    void Delete();
};


#endif