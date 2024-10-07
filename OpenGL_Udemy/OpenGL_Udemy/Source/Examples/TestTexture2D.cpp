#include <TestTexture2D.h>

namespace Tests
{
    TestTexture2D::TestTexture2D()
       :m_projection(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_translationA(0, 0, 0), m_translationB(0, 0, 0)
    {
        float points[] = {
           
             -150.0f, -50.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,0,0,
             -50.0f,  -50.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,
             -50.0f,   50.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1,1,0,
             -150.0f,  50.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0,1,0,

              50.0f,  -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0,0,1,
              150.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,
              150.0f,  50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1,1,1,
              50.0f,   50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0,1,1,
        };
        
        unsigned int indices[12] = {
            0,1,2,2,3,0,
            4,5,6,6,7,4
        };

        const std::string shadersPaths[2]
        {
            "res/Shaders/VertexBasic.shader",
            "res/Shaders/FragBasic.shader"
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_compiler = std::make_unique<ShaderCompiler>("res/Shaders/VertexBasic.shader", "res/Shaders/FragBasic.shader");
        m_vertexArray = std::make_unique<VertexArray>();

        m_vertexBuffer = std::make_unique<VertexBuffer>(points, 8 * 10 * sizeof(float));
       
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(4);
        layout.Push<float>(2);
        layout.Push<float>(1);

        m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
        m_indexBuffer = std::make_unique<IndexBuffer>(indices, 12);
        
        m_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
       
        //m_compiler->SetUniform4f("u_Color", 0, 0.2f, 0.2f, 1.0f);
        m_compiler->Bind();

        m_texture = std::make_unique<Texture>("res/Textures/UVMap.png");
        m_compiler->SetUniform1i("u_Textures", 0);

        m_texture = std::make_unique<Texture>("res/Textures/UVMap2.png");
        m_compiler->SetUniform1i("u_Textures", 1);
        
        
    }
    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
    }
    
    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.5f,0.0f,0.0f,1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_texture->Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp = m_projection * m_view * model;
            m_compiler->Bind();
            m_compiler->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_compiler);
        }
      
    }
    
    void TestTexture2D::OnImGuiRender()
    { 
        ImGui::Text("imGUI Exemple");                           
        ImGui::SliderFloat3("translationA", &m_translationA.x, 0.0f, 1080.0f);
        ImGui::SliderFloat3("translationB", &m_translationB.x, 0.0f, 1080.0f);
        ImGui::Text("FPS: ", 1000.0f/ ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
       
    }
}
