#include "UIElement.h"

UIElement::UIElement() {}

UIElement::UIElement(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color)
{
    Position = pos;
    Size = size;
    Color = color;
    Rotation = 0.0f;
    textureSlot = slot;
    IsSolid = false;
    Destroyed = false;
}

UIElement::~UIElement() {}

void UIElement::OnRender(UniformManager* uniformManager, RendererObject* rendererObject, TextureManager* textureManager, glm::mat4& m_MVP)
{
    uniformManager->SetUniformMat4f(rendererObject->shader->
        m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);

    uniformManager->SetUniform1i(rendererObject->shader->
        m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Texture"], textureSlot);
}

void UIElement::Draw(Renderer* renderer, RendererObject* rendererObject)
{
    renderer->Draw(rendererObject);
}
