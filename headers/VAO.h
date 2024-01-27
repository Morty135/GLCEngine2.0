#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include <VBO.h>

class VAO
{
public:
    unsigned int ID;

    VAO();

    void LinkAttrib(VBO &VBO, unsigned int layout);

    void Bind();
    
    void Unbind();

    void Delete();
};


#endif