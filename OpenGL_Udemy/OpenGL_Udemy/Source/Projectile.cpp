#include "Projectile.h"

Projectile::Projectile() {};
Projectile::Projectile(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color, float velocity) : GameObject()
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
Projectile::~Projectile() {}

void Projectile::Move()
{
    this->Position.y += 0.01f;
}

 void Projectile::OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
    TextureManager* textureManager, glm::mat4& m_MVP)
 {
    uniformManager->SetUniformMat4f(rendererObject->shader->
        m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);

    uniformManager->SetUniform1i(rendererObject->shader->
        m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Texture"], textureSlot);

}

 void Projectile::Draw(Renderer* renderer, RendererObject* rendererObject)
 {
     renderer->Draw(rendererObject);
 }

 void Projectile::OnHit()
 {
     Destroyed = true;
     IsSolid = false;
 }