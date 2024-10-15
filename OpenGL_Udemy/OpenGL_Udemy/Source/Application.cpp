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
#include <UniformsManager.h>

const std::string shadersFolderPath;
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
glm::mat4 m_Model;
glm::mat4 m_Projection;
glm::mat4 m_View;
glm::mat4 m_MVP;

glm::vec3 m_translation;
//GLuint vertexArrayObject;
//GLuint vertexBufferObject;

float positions[] = {
    // -0.5f, 0.0f, 0.0f,   /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,0,0,*/
    // 0.0f, 0.5f, 0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/
    // 0.5f, 0.0f,0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1,1,0,*/
    // 0.0f, -0.5f,0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/
    
     405.0f,  540.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,0,1,*/
     810.0f, 270.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,*/
     1215.0f,  540.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 1,1,1,*/
     810.0f,   810.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,*/
};

unsigned int indexes[] =
{
     0,1,2,
     2,3,0,
     //4,5,6,
     //6,7,4
};

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGl - Udemy", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    DebugLog(glEnable(GL_BLEND));
    DebugLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
   UniformManager uniformManager;
   UniformManager* uniformManager_ptr = &uniformManager;
   Shader shader(*uniformManager_ptr);
   

   VertexArrayObject vertexArrayObject;
   VertexBuffer vertexBuffer(positions, 4 * 3 * sizeof(float));

   VertexBufferLayout layout;
   layout.Push<float>(3);
   //layout.Push<float>(4);
   //layout.Push<float>(2);
   //layout.Push<float>(1);
   
   vertexArrayObject.AddBuffer(vertexBuffer, layout);
   
   IndexBuffer indexBuffer(indexes, 6);
    m_Projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    
    m_MVP = m_Projection * m_View * m_Model;
   
   shader.Bind();
  
   Renderer renderer;
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
    

    float increment = 0.0001f;
    //---------------- IMGUI -------------
    renderer.Unbind(rendererObject);
    std::cout <<"----------Rendering-----------" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        //glViewport(0, 0, WIDTH, HEIGHT);
        renderer.Clear();
        rendererObject.shader.Bind();

        uniformManager_ptr->SetUniform4f(rendererObject.shader.m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Color"], 1.0f, 0.0f, 0.0f, 1);
        uniformManager_ptr->SetUniformMat4f(rendererObject.shader.m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);
        renderer.Draw(rendererObject);

        //m_translation = glm::vec3(1,1,1);
        //m_MVP = m_Projection * m_View * glm::translate(glm::mat4(1.0f), m_translation);;

        
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
       
        renderer.Unbind(rendererObject);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //ImGui_ImplGlfwGL3_Shutdown();
    //ImGui::DestroyContext();

    glfwTerminate();
    return 0;
};