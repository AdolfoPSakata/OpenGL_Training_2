#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <OpenGLDebugger.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_Map>

#define SHADER_SOURCE_MAP std::unordered_map<std::string, std::unordered_map<std::string, ShaderSource>>

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    TESSELETION = 2,
    GEOMETRY = 3,
    POSTPROCESSING = 4
};

struct ShaderSource
{
    ShaderType type;
    GLuint id;
    std::string name;
    std::string source;
};

struct ShaderComposition
{
    unsigned int vertexSource;
    unsigned int fragmentSource;
    //TODO:: Implement others shaders 
};


class Shader
{
public:
    Shader(std::string& paths);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    unsigned int CreateProgram(const std::string& vertexName, const std::string& fragName);

    //TODO: General function, maybe
    void SetUniform4f(const std::string& name, float r, float g, float b, float a);
    void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
    void SetUniform1i(const std::string& name, int i);
    void SetUniform1f(const std::string& name, float f);

private:
    unsigned int m_ShaderID;
    mutable std::unordered_map<std::string, ShaderSource> m_VertexSources = {};
    mutable std::unordered_map<std::string, ShaderSource> m_FragmentSources = {};
    mutable std::unordered_map<std::string, ShaderSource> m_TesseletionSurces = {};
    mutable std::unordered_map<std::string, ShaderSource> m_GeometrySources = {};
    mutable std::unordered_map<std::string, ShaderSource> m_PostProcessingSources = {};

    mutable std::unordered_map<std::string,
        std::unordered_map<std::string, ShaderSource>> m_ShaderSources =
    {
       {"vertex", m_VertexSources},
       {"fragment", m_FragmentSources},
       {"tesseletion", m_TesseletionSurces},
       {"geometry", m_GeometrySources},
       {"postProcessing", m_PostProcessingSources}
    };

    void PreCompileShaders(std::string& shaderFolderPath);
    void SanitizeName(std::string& path);
    ShaderSource ParseShader(const std::string& name, const std::string& path);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void RegisterShaderSource(ShaderSource& shader, SHADER_SOURCE_MAP& shadersMap);
    int ProgramSetup(const ShaderComposition& source);
    
    mutable std::unordered_map<std::string, GLint> m_uniformLocationCache;

    GLint GetUniformLocation(const std::string& name) const;
};