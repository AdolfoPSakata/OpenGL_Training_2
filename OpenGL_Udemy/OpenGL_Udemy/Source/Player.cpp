#include "Player.h"

std::vector<Projectile> projectileVector;
Player::Player() {};
Player::Player(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color, float velocity) : GameObject()
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

Player::~Player() {}

void Player::Shoot()
{
    Projectile projectile = Projectile(
        glm::vec2(this->Position.x + 0.1f / 2, this->Position.y + 0.1f),
        glm::vec2(0.01f, 0.05f),
        3,
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        1.0f);

    projectileVector.emplace_back(projectile);
    shots++;
    std::cout << projectile.Position.x << " - " << projectile.Position.y << std::endl;
}

glm::mat4 Player::Move()
{
    glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(this->Position.x * Velocity, this->Position.y, 0));
    Model = glm::scale(Model, glm::vec3(this->Size, 1.0f));
    
    return Model;
}

void Player::OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
    TextureManager* textureManager, glm::mat4& m_MVP)
{
    uniformManager->SetUniformMat4f(rendererObject->shader->
        m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);

    uniformManager->SetUniform1i(rendererObject->shader->
        m_ShaderSources["fragment"]["zBasicFrag"].uniformLocation["u_Texture"], textureSlot);
}

void Player::Draw(Renderer* renderer, RendererObject* rendererObject)
{
    renderer->Draw(rendererObject);
}