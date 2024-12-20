#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <Definitions.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glfw/glfw3.h>

#include <Definitions.h>

#include <iostream>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed);
    
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    static bool hasMoved;
    static glm::vec3 m_currentPosition;
    static glm::vec3 m_lastPosition;
    float MovementSpeed;
   
   static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
   static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
   static void Zoom(GLFWwindow* window, double zPos, double xPos);
    glm::vec3 GetValues();
    float GetZoom();
    void CreateCallbacks(GLFWwindow* window);
    glm::mat4 GetViewMatrix();
private:
#endif
};