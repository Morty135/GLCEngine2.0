#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

class VAO
{
public:
    unsigned int ID;

    VAO();

    void Bind();

    void Delete();
};


#endif