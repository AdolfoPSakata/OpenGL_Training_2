#include "Enemy.h"

Enemy::Enemy() {};
Enemy::Enemy(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color, float velocity) : GameObject()
{
    Position = pos;
    Size = size;
    Velocity = velocity;
    Color = color;
    Rotation = 0.0f;
    textureSlot = slot;
    IsSolid = false;
    Destroyed = false;
}

Enemy::~Enemy() {}

void Enemy::Move(float deltaTime)
{
    if (currentMoveIndex <= 4)
    {
        step += deltaTime * 0.5f;
        if (step >= 1)
        {
            Position.x += 0.05f;
            currentMoveIndex++;
            step = 0;
        }
    }
    else if (currentMoveIndex == 5 || currentMoveIndex == 10)
    {
        step += deltaTime * 0.5f;
        if (step >= 1)
        {
            Position.y -= 0.1f;
            currentMoveIndex++;
            step = 0;
        }
    }
    else if (currentMoveIndex <= 9)
    {
        step += deltaTime * 0.5f;
        if (step >= 1)
        {
            Position.x -= 0.05f;
            currentMoveIndex++;
            step = 0;
        }
    }
    else
    {
        currentMoveIndex = 1;
        step = 0;
    }
}

void Enemy::OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
    TextureManager* textureManager, glm::mat4& m_MVP)
{
    uniformManager->SetUniformMat4f(rendererObject->shader->
        m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);

    uniformManager->SetUniform1i(rendererObject->shader->
        m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Texture"], textureSlot);

}

void Enemy::Draw(Renderer* renderer, RendererObject* rendererObject)
{
    renderer->Draw(rendererObject);
}

void Enemy::OnHit()
{
    Destroyed = true;
    IsSolid = false;
}
