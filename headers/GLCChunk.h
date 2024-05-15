#ifndef GLCCHUNK_H
#define GLCCHUNK_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <GLCCamera.h>
#include <GLCShader.h>
#include <GLCMesh.h>
#include <PerlinNoise.h>



class GLCChunk
{
    public:
        std::vector <vertex> vertices;
        std::vector <unsigned int> indices;
        
        std::vector<glm::vec2> translations;
        std::vector<GLCTextureStruct> textures;

        int gridSize = 100;
        float cellSize = 1;
        float frequency = 1;

        float xOffset = 0, zOffset = 0;
        
        GLCMesh ChunkMesh;

	    GLCChunk(int gridSize, float cellSize, float frequency, int X, int Y);

        GLCMesh GenerateMesh();

	    void Draw(GLCShader& shader, GLCCamera& camera);
        void Delete();
};



#endif