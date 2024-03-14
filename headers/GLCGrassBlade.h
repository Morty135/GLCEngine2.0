#ifndef GLCGRASSBLADE_H
#define GLCGRASSBLADE_H

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





class GLCGrassBlade
{
    public:
        std::vector <unsigned int> indices = 
        {
            0, 0,
            1, 0,
            1, 1,
            0, 1
        };

        glm::mat4 Transform = glm::mat4(1.0f);

        unsigned int instances;

	    VAO VAO;

	    GLCGrassBlade(unsigned int instances);

	    void Draw(GLCShader& shader, GLCCamera& camera);
        void Delete();
};



#endif