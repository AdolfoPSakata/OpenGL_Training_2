#pragma once
#include <GameObject.h>
#include <Projectile.h>
#include <RenderManager.h>

class Player : public GameObject
{
public:
    Player();
    Player(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color = glm::vec4(1.0f), float velocity = 1.0f);
    ~Player();
    
    int shots = 0;
    void OnRender(UniformManager* uniformManager, RendererObject* rendererObject, TextureManager* textureManager, glm::mat4& m_MVP);
    void Draw(Renderer* renderer, RendererObject* rendererObject);
    void Shoot();
    //void Die();
    //void LoseLife();
    glm::mat4 Move();
   
    std::vector<Projectile> projectileVector;
};
