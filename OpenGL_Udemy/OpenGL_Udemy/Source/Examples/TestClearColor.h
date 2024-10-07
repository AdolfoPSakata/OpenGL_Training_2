#pragma once

#include <Test.h>
#include <OpenGLDebugger.h>
#include <Renderer.h>
#include <imgui/imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tests
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}