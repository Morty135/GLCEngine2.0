#ifndef GLCTERRAIN_H
#define GLCTERRAIN_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <thread>

#include <GLCCamera.h>
#include <GLCShader.h>
#include <GLCChunk.h>



class GLCTerrain
{
    public:
        std::vector<GLCChunk> chunks;

        int gridSize = 100;
        float cellSize = 1;
        float frequency = 1;

        int prevX = 0;
        int prevZ = 0;

	    GLCTerrain(int gridSize, float cellSize, float frequency);

        double restrictToRange(double value) 
        {
            return std::max(0.0, std::min(1.0, value));
        }

	    void Draw(GLCShader& GroundShader, GLCShader& GrassShader, GLCCamera& camera, glm::mat4& playerTransform);
        void Delete();
};



#endif