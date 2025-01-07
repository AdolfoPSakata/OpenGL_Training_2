#pragma once
#include <GameObject.h>
#include <Projectile.h>
#include <RenderManager.h>

class UIElement : public GameObject
{
public:
	UIElement();
	UIElement(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color = glm::vec4(1.0f));
	~UIElement();
	void OnRender(UniformManager* uniformManager, RendererObject* rendererObject, TextureManager* textureManager, glm::mat4& m_MVP);
	void Draw(Renderer* renderer, RendererObject* rendererObject);
private:

};