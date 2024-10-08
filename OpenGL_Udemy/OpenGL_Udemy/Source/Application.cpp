#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw_gl3.h>
#include <GLM/glm.hpp>
#include <GLM/GTC/matrix_transform.hpp>
#include <GLM/GTC/type_ptr.hpp>

#include <OpenGLDebugger.h>
#include <Examples.h>
#include <Renderer.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>

std::string shadersFolderPath;
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
//GLuint vertexArrayObject;
//GLuint vertexBufferObject;

float positions[] =
{
    0.5f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f, 0.5f,
};

float indexes[] =
{
    0,1,2,
    2,3,0
};

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

   //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 400, "OpenGl - Udemy", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

  // DebugLog(glEnable(GL_BLEND));
  // DebugLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
   
   Renderer renderer;
   
   VertexArrayObject vertexArrayObject;
   VertexBuffer vertexBuffer(positions, 2 * 6 * sizeof(float));
   IndexBuffer indexBuffer(indexes, 6);

   VertexBufferLayout layout;
   layout.Push<float>(2);
   
   vertexArrayObject.AddBuffer(vertexBuffer, layout);
   
   shadersFolderPath = "OpenGL_Udemy\\Resources\\Shaders";
   Shader shader(shadersFolderPath);
   shader.CreateProgram("BasicVertex", "BasicFrag");
   shader.Bind();
  // shader.SetUniform4f("u_Color", 1, 1, 1, 1);
   
   RendererObject rendererObject = {
       vertexArrayObject,
       vertexBuffer,
       indexBuffer,
       shader,
   };

    //ImGui::CreateContext();
    //ImGui_ImplGlfwGL3_Init(window, true);
    //ImGui::StyleColorsDark();

    //---------------- IMGUI ------------- WIP
    //Imgui_Examples::Examples* currentExemple = nullptr;
    //Imgui_Examples::ExampleMenu* menu = new Imgui_Examples::ExampleMenu(currentExemple);
    //currentExemple = menu;

    //menu->RegisterExample<Imgui_Examples::TestClearColor>("Clear color");
    //menu->RegisterExample<Imgui_Examples::TestTexture2D>("Textures");
    //---------------- IMGUI -------------

    renderer.Unbind(rendererObject);
    std::cout <<"----------Rendering-----------" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw(rendererObject);
       //
        //shader.SetUniform4f("u_Color", 1, 1, 1, 1);
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
       // rendererObject.Unbind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //ImGui_ImplGlfwGL3_Shutdown();
    //ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}