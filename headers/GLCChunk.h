#ifndef GLCTERRAIN_H
#define GLCTERRAIN_H

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
#include <GLCMesh.h>
#include <PerlinNoise.h>



class GLCChunk
{
    public:
        std::vector <vertex> vertices;
        std::vector <unsigned int> indices;

        glm::mat4 Transform = glm::mat4(1.0f);
        
        std::vector<glm::vec2> translations;
        std::vector<GLCTextureStruct> textures;

        int gridSize = 1000;
        float cellSize = 0.1;
        float frequency = 0.05;
        
        GLCMesh ChunkMesh;

	    GLCChunk();

        GLCMesh GenerateMesh();

	    void Draw(GLCShader& shader, GLCCamera& camera);
        void Delete();
};



#endif