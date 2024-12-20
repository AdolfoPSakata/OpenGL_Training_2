#pragma once
#include <Definitions.h>
#include <OpenGLDebugger.h>
#include <IndexBuffer.h>
#include <VertexArrayObject.h>
#include <Shader.h>

#include <functional>

struct RendererObject
{
	VertexArrayObject* vao;
	VertexBuffer* vbu;
	IndexBuffer* ibo;
	Shader* shader;

	const void Unbind()
	{
		vao->Unbind();
		vbu->Unbind();
		ibo->Unbind();
		shader->Unbind();
	};
};

class Renderer {
public:
	void Draw(const RendererObject* renderObject);
	void Clear() const;
	void Unbind(const RendererObject* renderObject);

	//TODO: move to class
	//int GetUniformLocation(const int shader, const char* uniformString);
};