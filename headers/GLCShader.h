#ifndef GLCSHADER_H
#define GLCSHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string get_file_contents(const char* filePath);

class GLCShader
{
public:
    unsigned int ID;

    GLCShader(const char* vertexSourcePath, const char* fragmentSourcePath);

    void Use();

    void Delete();
};


#endif