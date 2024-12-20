#include <RenderManager.h>


RenderManager::RenderManager() {}
RenderManager::~RenderManager() {}

float positions[] = 
{
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
};

unsigned int indexes[] =
{
     0,1,2,
     2,3,0,
};

int RenderManager::Init()
{
     if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Space Invaders", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(window, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR" << std::endl;

    DebugLog(glEnable(GL_BLEND));
    DebugLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //TODO
    //Camera mainCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
    //mainCamera.CreateCallbacks(window);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    shader = new Shader(*uniformManager);
    //TODO: points * data size
    vertexBuffer = new VertexBuffer(positions, 4 * 6 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(4);
    layout.Push<float>(2);
    //TODO
    //layout.Push<float>(1);
    vertexArrayObject = new VertexArrayObject();
    vertexArrayObject->AddBuffer(vertexBuffer , layout);

    indexBuffer = new IndexBuffer(indexes, 12);

    m_Projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, -1.0f, 1.0f);
    m_Projection = glm::translate(m_Projection, glm::vec3(0, 0, -1.0f));
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 1));

    shader->Bind();

    textureManager = new TextureManager();
    textureManager->LoadTextures();

    rendererObject = new RendererObject {
        vertexArrayObject,
        vertexBuffer,
        indexBuffer,
        shader,
    };
    renderer->Unbind(rendererObject);
}

void RenderManager::StartDraw()
{
       renderer->Clear();
       rendererObject->shader->Bind();
}

void RenderManager::DrawEnd()
{
       renderer->Unbind(rendererObject);
       glfwSwapBuffers(window);
       glfwPollEvents();
}