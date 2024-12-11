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
#include <UniformsManager.h>
#include <Camera.h>
#include <Definitions.h>
#include <Texture.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <numbers>

#define _USE_MATH_DEFINES 
#include <math.h>

#define TO_RADIANS(x) (float) (x * (M_PI / 180))

const std::string shadersFolderPath;

glm::mat4 m_Model;
glm::mat4 m_Projection;
glm::mat4 m_View;
glm::mat4 m_MVP;

glm::vec3 m_translation;
//GLuint vertexArrayObject;
//GLuint vertexBufferObject;

float positions[] = {
     -1.5f, -1.5f, 0.0f,  /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,0,0,*/
     1.5f, -1.5f, 0.0f,/*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/
     1.5f, 1.5f, 0.0f,/*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1,1,0,*/
     -1.5f, 1.5f, 0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/
    
    // -1.5f, -1.5f, 0.0f,   /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,0,0,*/
    // 0.0f, -1.5f, 0.5f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/
    // 1.5f, -1.5f,0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1,1,0,*/
    // 0.0f, 1.5f,0.0f, /*-100.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,*/

    //-1.0f, -1.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,0,1,*/
    // 1.0f,  0.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,*/
    // 0.0f,  1.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 1,1,1,*/
    //-1.0f,  0.0f, 0.0f, /*0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,*/
};

unsigned int indexes[] =
{
     0,1,2,
     2,3,0

    //  0,3,1,
    // 1,3,2,
    // 2,3,0,
    // 0,1,2,
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

    glfwSetWindowUserPointer(window, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(10);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    DebugLog(glEnable(GL_BLEND));
    DebugLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Camera mainCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
    mainCamera.CreateCallbacks(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
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

    m_Projection = glm::perspective(45.0f, (GLfloat) WIDTH/ (GLfloat)HEIGHT, 0.0f, 100.0f);
    m_Projection = glm::translate(m_Projection, glm::vec3(0, 0, -10.0f));
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
   
    m_MVP = m_Projection * m_View * m_Model;
    
    shader.Bind();
  
    Renderer renderer;

    std::unique_ptr<Texture> m_texture = std::make_unique<Texture>("Resources/Textures/1.png");
   
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
    

    float increment = 0.1f;
    float position = 0.0f;
   // m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0, 0));
    //---------------- IMGUI -------------
    renderer.Unbind(rendererObject);
    std::cout <<"----------Rendering-----------" << std::endl;


   /* m_Model = glm::rotate(m_Model, TO_RADIANS(0), glm::vec3(0,0,1));
    m_Model = glm::scale(m_Model, glm::vec3(2));*/
    //m_Model = glm::translate(m_Model, glm::vec3(0, 0, 0));
    while (!glfwWindowShouldClose(window))
    {
        //glViewport(0, 0, WIDTH, HEIGHT);
        renderer.Clear();
        rendererObject.shader.Bind();

        uniformManager_ptr->SetUniformMat4f(rendererObject.shader.m_ShaderSources["vertex"]["BasicVertex"].uniformLocation["u_MVP"], m_MVP);
        uniformManager_ptr->SetUniform4f(rendererObject.shader.m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Color"], 1.0f,1.0f,1.0f, 1.0f);
        uniformManager_ptr->SetUniform1i(rendererObject.shader.m_ShaderSources["fragment"]["BasicFrag"].uniformLocation["u_Texture"], 0);
        renderer.Draw(rendererObject);
        
//
// if (position > 180)
// {
//     increment = increment * -1;
// }
// else if (position < 0)
// {
//     increment = increment * -1;
// }
// //std::cout << increment << " - " << position << std::endl;
// position += increment;

        //m_Projection = glm::rotate(m_Projection, TO_RADIANS(1), glm::vec3(0, position, 0));
        //m_View +=  mainCamera.GetValues() * 0.001f;
       //m_View = glm::translate(m_View, mainCamera.GetValues() * 0.01f);
       //m_MVP = m_Projection * m_View * m_Model;


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