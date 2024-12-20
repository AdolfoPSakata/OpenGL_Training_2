#include <VertexArrayObject.h>

VertexArrayObject::VertexArrayObject()
{
    DebugLog(glGenVertexArrays(1, &m_VertexArrayObject));
    DebugLog(glBindVertexArray(m_VertexArrayObject));
}

VertexArrayObject::~VertexArrayObject()
{
    DebugLog(glDeleteVertexArrays(1, &m_VertexArrayObject));
}

void VertexArrayObject::AddBuffer(const VertexBuffer* vertexBuffer, const VertexBufferLayout& layout)
{
    VertexArrayObject::Bind();
    vertexBuffer->Bind();

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        DebugLog(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        DebugLog(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArrayObject::Bind() const
{
    DebugLog(glBindVertexArray(m_VertexArrayObject));
}
void VertexArrayObject::Unbind() const
{
    DebugLog(glBindVertexArray(0));
}
