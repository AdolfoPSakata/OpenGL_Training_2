#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <Test.h>
#include <OpenGLDebugger.h>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <IndexBuffer.h>

#include <Texture.h>
#include <Memory.h>

namespace Tests
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		glm::mat4 m_projection;
		glm::mat4 m_view;

		std::unique_ptr<VertexArray> m_vertexArray;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<ShaderCompiler> m_compiler;
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr < VertexBuffer> m_vertexBuffer;
	};
}