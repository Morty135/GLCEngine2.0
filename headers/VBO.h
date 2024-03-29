#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <vector>

struct vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
};

class VBO
{
public:
    unsigned int ID;

    VBO(std::vector<vertex>& vertices);

    void Bind();

    void Unbind();

    void Delete();
};

#endif