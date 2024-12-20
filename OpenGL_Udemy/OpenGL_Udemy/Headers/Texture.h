#pragma once

#include <Definitions.h>
#include <stb_image.h>
#include <OpenGLDebugger.h>

class Texture
{
public:
	Texture(const std::string& path, unsigned int slot);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_TextureID; }
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width;
	int m_Height;
	int m_BytesPerPixel;
};
