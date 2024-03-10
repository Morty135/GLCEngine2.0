#ifndef GLCMODEL_H
#define GLCMODEL_H

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
        void Draw(GLCShader &shader, GLCCamera& camera);	
    private:

        std::vector<GLCMesh> meshes;
        std::string directory;
        std::vector<GLCTextureStruct> textures_loaded;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        GLCMesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<GLCTextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif