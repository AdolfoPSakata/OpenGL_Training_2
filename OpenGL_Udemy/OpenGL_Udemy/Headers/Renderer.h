#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <OpenGLDebugger.h>
#include <IndexBuffer.h>
#include <VertexArrayObject.h>
#include <Shader.h>

#include <functional>

struct RendererObject
{
	VertexArrayObject& vao;
	VertexBuffer& vbu;
	IndexBuffer& ibu;
	Shader& shader;
	const void Unbind()
	{
		vao.Unbind();
		vbu.Unbind();
		ibu.Unbind();
		shader.Unbind();
	};
};

class Renderer {
public:
	void Draw(const RendererObject& renderObject);
	void Clear() const;

	//TODO: move to class
	int GetUniformLocation(const int shader, const char* uniformString);
	void Unbind(const RendererObject& renderObject);
};