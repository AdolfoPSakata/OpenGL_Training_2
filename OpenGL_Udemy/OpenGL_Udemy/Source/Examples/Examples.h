#pragma once
#include <imgui/imgui.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

namespace Imgui_Examples
{
	class Examples
	{
	public:
		Examples() {}
		virtual ~Examples() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class ExampleMenu : public Examples
	{
	public:
		ExampleMenu(Examples*& currentExample_ptr);

		virtual void OnImGuiRender() override;

		template<typename T>
		void RegisterExample(const std::string& name)
		{
			std::cout << "Registered Example - " << name << std::endl;
			m_Examples.push_back(std::make_pair(name, []()
				{ return new T(); }));
		};

	private:
		Examples*& m_CurrentExample;
		std::vector<std::pair<std::string, std::function<Examples* ()>>> m_Examples;
	};
}