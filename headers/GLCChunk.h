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
#include <GLCModel.h>
#include <PerlinNoise.h>



class GLCChunk
{
    public:
        std::vector <vertex> vertices;
        std::vector <unsigned int> indices;
        
        std::vector<glm::vec3> instaceOffsets;
        std::vector<GLCTextureStruct> textures;

        int gridSize = 100;
        float cellSize = 1;
        float frequency = 1;

        float xOffset = 0, zOffset = 0;

        //siv::PerlinNoise perlinFunc{ std::random_device{}  };
        siv::PerlinNoise perlinFunc{ 777 };
        
        GLCMesh ChunkMesh;
        GLCModel Grass;

	    GLCChunk(int gridSize, float cellSize, float frequency, int X, int Y);

        GLCMesh GenerateMesh();

        GLCModel GenerateGrass();

	    void Draw(GLCShader& GroundShader, GLCShader& GrassShader, GLCCamera& camera);
        void Delete();
};



#endif