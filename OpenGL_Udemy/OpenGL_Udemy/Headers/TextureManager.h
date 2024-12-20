#pragma once
#include <Texture.h>

#include <vector>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_Map>

#define TEXTURE_SOURCE_MAP mutable std::unordered_map<std::string, unsigned int>

class TextureManager
{
public:
	unsigned int slot = 0;
	TextureManager();
	~TextureManager();
	void LoadTextures();
	void RegisterTexture(std::string name, unsigned int slot);
	unsigned int GetTextureSlot(std::string name);
	const std::string TexturesFolderPath = "OpenGL_Udemy\\Resources\\Textures";
	TEXTURE_SOURCE_MAP  textureLocations = {};
	
private:

};
