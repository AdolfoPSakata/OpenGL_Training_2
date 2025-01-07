#pragma once
#include "Definitions.h"
#include <Renderer.h>
#include <iostream>
#include <map>
#include "freetype/ft2build.h"
#include FT_FREETYPE_H

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	int Init();
	void RenderText(UniformManager* uniformManager, RendererObject* rendererObject, std::string text, Renderer* renderer, float x, float y, float scale, glm::vec3 color);
private:
	
};
