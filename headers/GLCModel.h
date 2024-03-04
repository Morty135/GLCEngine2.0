#ifndef GLCMODEL_H
#define GLCMODEL_H

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
#include <GLCTexture.h>
#include <GLCMesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class GLCModel 
{
    public:
        GLCModel(char *path)
        {
            loadModel(path);
        }
        void Draw(GLCShader &shader);	
    private:

        std::vector<GLCMesh> meshes;
        std::string directory;

        void loadModel(std::string path);

        void processNode(aiNode *node, const aiScene *scene);

        GLCMesh processMesh(aiMesh *mesh, const aiScene *scene);

        void Draw(GLCShader &shader,GLCCamera& camera)
        {
            for(unsigned int i = 0; i < meshes.size(); i++)
                meshes[i].Draw(shader, camera);
        }  
        std::vector<GLCTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};


#endif