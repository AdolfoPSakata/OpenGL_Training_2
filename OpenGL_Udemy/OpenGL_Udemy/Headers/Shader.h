#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <OpenGLDebugger.h>
#include <UniformsManager.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_Map>

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    TESSELETION = 2,
    GEOMETRY = 3,
    POSTPROCESSING = 4
};

typedef struct ShaderSource
{
    ShaderType type;
    GLint id;
    std::string name;
    std::string source;
    mutable std::unordered_map<std::string, GLint> uniformLocation;
};

typedef struct ShaderComposition
{
    unsigned int vertexSource;
    unsigned int fragmentSource;
    unsigned int vertexUniformCount;
    unsigned int fragUniformCount;
    std::vector<std::string> vertexStrings;
    std::vector<std::string> fragStrings;
    //TODO:: Implement others shaders 
};

#define SHADER_SOURCE_MAP mutable std::unordered_map<std::string, std::unordered_map<std::string, ShaderSource>>

class Shader
{
public:
    Shader(UniformManager& uniformManager);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    unsigned int CreateProgram(const std::string& vertexName, const std::string& fragName);
    SHADER_SOURCE_MAP m_ShaderSources =
    {
       {"vertex", std::unordered_map<std::string, ShaderSource> {}},
       {"fragment", std::unordered_map<std::string, ShaderSource> {}},
       {"tesseletion", std::unordered_map<std::string, ShaderSource> {}},
       {"geometry", std::unordered_map<std::string, ShaderSource> {}},
       {"postProcessing", std::unordered_map<std::string, ShaderSource> {}},
    };

    GLint m_ShaderID;
private:
    UniformManager m_UniformManager;
    const std::string m_ShaderPath = "OpenGL_Udemy\\Resources\\Shaders";

    void PreCompileShaders(const std::string& shaderFolderPath);
    void SanitizeName(std::string& path);
    ShaderSource ParseShader(const std::string& name, const std::string& path);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void RegisterShaderSource(ShaderSource& shader, SHADER_SOURCE_MAP& shadersMap);
    int ProgramSetup( const ShaderComposition& source);
};