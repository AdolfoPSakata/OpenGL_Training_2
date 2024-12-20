#include <camera.h>

bool Camera::hasMoved = false;
glm::vec3 Camera::m_lastPosition = glm::vec3(0);
glm::vec3 Camera::m_currentPosition = glm::vec3(0);

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed)
    : Position(position), Front(front), Up(up), MovementSpeed(speed) {}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GL_TRUE);
   //if (key == GLFW_KEY_S)
   //     Position -= MovementSpeed * Front;
   // if (key == GLFW_KEY_A)
   //     Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
   // if (key == GLFW_KEY_D)
   //     Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
}

void Camera::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
    if (Camera::hasMoved)
    {
        Camera::m_currentPosition = glm::normalize(glm::vec3(-xPos , yPos, 1));
        Camera::hasMoved = true;
    }
    Camera::m_currentPosition = glm::normalize(glm::vec3(-xPos, yPos,1));
    Camera::m_lastPosition = Camera::m_currentPosition;
}

void Camera::Zoom(GLFWwindow* window, double xPos, double yPos)
{
    std::cout << xPos << " - " << yPos << std::endl;

    if (Camera::hasMoved)
    {
        Camera::m_currentPosition *= glm::vec3(0, 0, yPos);
        Camera::hasMoved = true;
    }
    Camera::m_currentPosition *= glm::vec3(0, 0, yPos * 2);
    Camera::m_lastPosition = Camera::m_currentPosition;
}

glm::vec3 Camera::GetValues()
{
   //std::cout << " --------------------------- " <<  std::endl;
   //std::cout << m_currentPosition.x << " - " << m_currentPosition.x << std::endl;
   //std::cout << m_currentPosition.y << " - " << m_currentPosition.y << std::endl;
   //std::cout << m_currentPosition.z << " - " << m_currentPosition.z << std::endl;

    return m_currentPosition;
}

void Camera::CreateCallbacks(GLFWwindow* window)
{
    glfwSetKeyCallback(window, HandleKeys);
    glfwSetCursorPosCallback(window, HandleMouse);
    glfwSetScrollCallback(window, Zoom);
}

