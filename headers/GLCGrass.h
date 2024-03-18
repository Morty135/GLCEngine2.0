#ifndef GLCGRASS_H
#define GLCGRASS_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <VAO.h>
#include <EBO.h>
#include <GLCCamera.h>
#include <GLCShader.h>



class GLCGrass
{
    public:
        std::vector <vertex> vertices;
        std::vector <unsigned int> indices;

        glm::mat4 Transform = glm::mat4(1.0f);
        unsigned int instances = 4000;
        
        std::vector<glm::vec2> translations;

	    VAO VAO;

	    GLCGrass();

	    void Draw(GLCShader& shader, GLCCamera& camera);
        void Delete();
};



#endif