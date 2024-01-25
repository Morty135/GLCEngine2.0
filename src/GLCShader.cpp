#include <GLCShader.h>


std::string get_file_contents(const char* filePath)
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path fullPath = currentPath / filePath;

    std::ifstream shaderFile(fullPath);

    if (!shaderFile.is_open()) 
    {
        std::cerr << "Unable to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

GLCShader::GLCShader(const char* vertexSourcePath, const char* fragmentSourcePath)
{
    std::string vertexCodeString = get_file_contents(vertexSourcePath);
    std::string fragmentCodeString = get_file_contents(fragmentSourcePath);

    const char* vertexSource = vertexCodeString.c_str();
    const char* fragmentSource = fragmentCodeString.c_str();

    //compiles the vertex shader from source
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    //the same for fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GLCShader::Use()
{
    glUseProgram(ID); 
}

void GLCShader::Delete()
{
    glDeleteProgram(ID);
}