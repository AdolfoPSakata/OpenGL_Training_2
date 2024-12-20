#include "TextureManager.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{

}

void TextureManager::LoadTextures()
{
    const std::filesystem::path finalPath{ SOLUTION_DIR + TexturesFolderPath };

    for (const auto& entry : std::filesystem::directory_iterator(finalPath)) 
    {
            std::string name = entry.path().filename().string();
            std::string path = entry.path().string();;
            std::cout << "dir: " << name << " - " << path << std::endl;

            RegisterTexture(name, slot);
            slot++;
    }
}

void TextureManager::RegisterTexture(std::string name,unsigned int slot)
{
    new Texture("Resources/Textures/" + name, slot);
    textureLocations[name] = slot;
}

unsigned int TextureManager::GetTextureSlot(std::string name)
{
    return textureLocations.at(name);
}
