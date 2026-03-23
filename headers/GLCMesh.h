#ifndef GLCMESH_H
#define GLCMESH_H

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



struct GLCTextureStruct {
    unsigned int id;
    std::string type;
    std::string path;
};



class GLCMesh
{
    public:
        std::vector <vertex> vertices;
        std::vector <unsigned int> indices;
        std::vector <GLCTextureStruct> textures;

        glm::mat4 Transform = glm::mat4(1.0f);

	    VAO VAO;

	    GLCMesh(std::vector <vertex>& vertices, std::vector <unsigned int>& indices, std::vector <GLCTextureStruct>& textures);

	    void Draw(GLCShader& shader, GLCCamera& camera);
        void Delete();
};



#endif