#pragma once

#include <Definitions.h>
#include <OpenGLDebugger.h>
#include <UniformsManager.h>
#include <Renderer.h>
#include <Camera.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <numbers>
#include <TextureManager.h>
#include <Texture.h>
#include <Player.h>
#include <Enemy.h>

class RenderManager
{

public:
    RenderManager();
    ~RenderManager();
  
    GLFWwindow* window;
    Renderer* renderer;
    UniformManager* uniformManager;
    RendererObject* rendererObject;
    TextureManager* textureManager;

    const std::string shadersFolderPath;
    
    glm::mat4 m_Model;
    glm::mat4 m_Projection;
    glm::mat4 m_View;
    glm::mat4 m_MVP;
    glm::vec3 m_translation;
    
    VertexArrayObject* vertexArrayObject;
    VertexBuffer* vertexBuffer;
    Shader* shader;
    Shader* textShader;
    IndexBuffer* indexBuffer;

    int Init();
    void StartDraw();
    void DrawEnd();
    
private:
};