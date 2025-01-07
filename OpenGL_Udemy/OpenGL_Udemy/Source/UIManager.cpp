#include "UIManager.h"
#include <Game.h>

//UIElement lives;
std::vector<UIElement> elements = {};
glm::mat4 m_Projection;
glm::mat4 m_View;
glm::mat4 MVP;

UIManager::UIManager() {}
UIManager::~UIManager() {}

void UIManager::CreateElement()
{
    UIElement element = UIElement(
        glm::vec2(-0.7f, -0.5f),
        glm::vec2(0.1f, 0.1f),
        Game::renderManager->textureManager->GetTextureSlot("Error_Texture.png"),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    
    elements.push_back(element);
}

void UIManager::Init()
{
    m_Projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, -1.0f, 1.0f);
    m_Projection = glm::translate(m_Projection, glm::vec3(0, 0, -1.0f));
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 1));

    CreateElement();
}

void UIManager::DrawElements(RenderManager* renderManager, glm::mat4 test)
{
    for (int i = 0; i < elements.size(); i++)
    {
        glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(elements[i].Position.x, elements[i].Position.y, 0));
        Model = glm::scale(Model, glm::vec3(elements[i].Size.x, elements[i].Size.y, 1));

        MVP = m_Projection * Model;

        elements[i].OnRender(renderManager->uniformManager, renderManager->rendererObject,
            renderManager->textureManager, MVP);

        elements[i].Draw(renderManager->renderer, renderManager->rendererObject);
    }
}




