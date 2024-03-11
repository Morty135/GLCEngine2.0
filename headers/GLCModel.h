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


unsigned int TextureFromFile(const char *path, const std::string &directory);


class GLCModel 
{
    public:
        std::vector<GLCMesh> meshes;
        std::string directory;
        std::vector<GLCTextureStruct> textures_loaded;

        glm::mat4 Transform = glm::mat4(1.0f);

        GLCModel(std::string const &path)
        {
            loadModel(path);
        }
        void Draw(GLCShader &shader, GLCCamera& camera);
        void Delete();
    private:
        void loadModel(std::string const &path);
        void processNode(aiNode *node, const aiScene *scene);
        GLCMesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<GLCTextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif