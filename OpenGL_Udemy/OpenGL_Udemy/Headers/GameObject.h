#pragma once
#include <Definitions.h>
#include <Texture.h>
#include <TextureManager.h>
#include <Renderer.h>

class GameObject
{
public:
    //explicit  GameObject();
    //explicit GameObject(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color = glm::vec4(1.0f), float velocity = 1.0f);
   
    bool IsAlive;
    bool IsSolid;
    bool Destroyed;
    float Rotation;
    float Velocity;
    int Lives;
   
    glm::vec2 Position;
    glm::vec2 Size;
    glm::vec4 Color;
    unsigned int textureSlot;

    virtual void Draw(Renderer* renderer, RendererObject* rendererObject) = 0;
    virtual void OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
        TextureManager* textureManager, glm::mat4& m_MVP) = 0;
private:
};