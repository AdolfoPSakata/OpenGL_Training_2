#include <IndexBuffer.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_Count(count)
{
    //to ensure that a unsigned int is equal to a GLuint
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))

    unsigned int buffer;
    DebugLog(glGenBuffers(1, &m_IndexBufferID));
    DebugLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID));
    DebugLog(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    DebugLog(glDeleteBuffers(1, &m_IndexBufferID));
}

void IndexBuffer::Bind() const
{
    DebugLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID));
}

void IndexBuffer::Unbind() const
{
    DebugLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

