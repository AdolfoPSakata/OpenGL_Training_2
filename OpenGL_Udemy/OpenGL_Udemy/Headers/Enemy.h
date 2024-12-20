#pragma once
#include <GameObject.h>

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(glm::vec2 pos, glm::vec2 size, unsigned int slot, glm::vec4 color = glm::vec4(1.0f), float velocity = 1.0f);
	~Enemy();

	void Move(float deltaTime);
	void OnRender(UniformManager* uniformManager, RendererObject* rendererObject,
		TextureManager* textureManager, glm::mat4& m_MVP);
	void Draw(Renderer* renderer, RendererObject* rendererObject);
	void OnHit();
	int currentMoveIndex = 1;
	float step = 0;
private:

};