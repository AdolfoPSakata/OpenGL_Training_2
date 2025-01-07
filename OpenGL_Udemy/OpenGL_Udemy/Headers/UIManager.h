#pragma once
#include "UIElement.h"


class UIManager
{
public:
	UIManager();
	~UIManager();

	
	void CreateElement();
	
	void Init();
	void DrawElements(RenderManager* renderManager, glm::mat4 test);
private:
};

