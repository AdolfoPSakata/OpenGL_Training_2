#include <Texture.h>

Texture::Texture(const std::string& path, unsigned int slot)
    : m_FilePath(path), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BytesPerPixel(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BytesPerPixel, 0);

    DebugLog(glGenTextures(1, &m_TextureID));
    DebugLog(glBindTexture(GL_TEXTURE_2D, m_TextureID))

    DebugLog(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    DebugLog(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    DebugLog(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    DebugLog(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    DebugLog(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

    Bind(slot);
   
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    DebugLog(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind(unsigned int slot) const
{
    std::cout << "SLOT: " << slot << std::endl;
    DebugLog(glActiveTexture(GL_TEXTURE1 + slot));
    DebugLog(glBindTexture(GL_TEXTURE_2D, m_TextureID))
}

void Texture::Unbind() const
{
    DebugLog(glBindTexture(GL_TEXTURE_2D, 0));
}
