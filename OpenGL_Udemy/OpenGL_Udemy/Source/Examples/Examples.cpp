#include <Examples.h>
namespace Imgui_Examples
{
    ExampleMenu::ExampleMenu(Examples*& currentExample_ptr)
        : m_CurrentExample(currentExample_ptr)
    {}
    
    void ExampleMenu::OnImGuiRender()
    {
        for (auto& example : m_Examples)
        {
            if (ImGui::Button(example.first.c_str()))
                m_CurrentExample = example.second();
        }
    }
}