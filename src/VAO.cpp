#include <VAO.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::Bind()
{
    glGenVertexArrays(1, &ID);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}