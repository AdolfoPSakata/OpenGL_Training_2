#pragma once

#include <Definitions.h>

#include <OpenGLDebugger.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	
	void AddBuffer(const VertexBuffer* vertexBuffer, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_VertexArrayObject;
};

