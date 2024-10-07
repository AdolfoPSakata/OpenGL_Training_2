#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw_gl3.h>
#include <GLM/glm.hpp>
#include <GLM/GTC/matrix_transform.hpp>
#include <GLM/GTC/type_ptr.hpp>

#include <OpenGLDebugger.h>
#include <Examples.h>
#include <Shader.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>

std::string shadersFolderPath;
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
GLuint vertexArrayObject;
GLuint vertexBufferObject;


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGl - Udemy", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    DebugLog(glEnable(GL_BLEND));
    DebugLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    shadersFolderPath = "OpenGL_Udemy\\Resources\\Shaders";
    Shader shader(shadersFolderPath);
    //TODO: Remove Hard Coded names
    unsigned int program = shader.CreateProgram("BasicFrag", "BasicVertex");

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //---------------- IMGUI ------------- WIP
    Imgui_Examples::Examples* currentExemple = nullptr;
    Imgui_Examples::ExampleMenu* menu = new Imgui_Examples::ExampleMenu(currentExemple);
    currentExemple = menu;

    //menu->RegisterExample<Imgui_Examples::TestClearColor>("Clear color");
    //menu->RegisterExample<Imgui_Examples::TestTexture2D>("Textures");
    //---------------- IMGUI -------------

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //------------- IMGUI ------------ WIP
        //ImGui_ImplGlfwGL3_NewFrame();
        //if (currentExemple)
        //{
        //    currentExemple->OnUpdate(0.1f);
        //    currentExemple->OnRender();
        //    ImGui::Begin("Example Case");
        //
        //    if (currentExemple != menu && ImGui::Button("<-"))
        //    {
        //        delete currentExemple;
        //        currentExemple = menu;
        //    }
        //    currentExemple->OnImGuiRender();
        //    ImGui::End();
        //}
        //
        //ImGui::Render();
        //ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        //-------- IMGUI  --------------------

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}