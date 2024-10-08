#include <VertexBuffer.h>

//check this later or overcharge
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    unsigned int buffer;
    DebugLog(glGenBuffers(1, &m_VertexBufferID));
    DebugLog(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
    DebugLog(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    DebugLog(glDeleteBuffers(1, &m_VertexBufferID));
}

void VertexBuffer::Bind()  const
{

    DebugLog(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
}

void VertexBuffer::Unbind() const
{
    DebugLog(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

