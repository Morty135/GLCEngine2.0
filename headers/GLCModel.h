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



void loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}



void processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}



GLCMesh processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLCTexture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertex vertex;
        vertices.push_back(vertex);
    }
    if(mesh->mMaterialIndex >= 0)
    {

    }

    return GLCMesh(vertices, indices, textures);
}  

#endif