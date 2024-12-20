#pragma once
#include <GameObject.h>

class Projectile : public GameObject
{
public:
	Projectile();
	Projectile(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color = glm::vec4(1.0f), float velocity = 1.0f);
	~Projectile();

	//using GameObject::GameObject;

	void Move();

	void OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
		TextureManager* textureManager, glm::mat4& m_MVP);
	void Draw(Renderer* renderer, RendererObject* rendererObject);
	void OnHit();
private:

};

