#pragma once

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <IMGUI/imgui.h>
//#include <IMGUI/imgui_impl_glfw_gl3.h>
//#include <GLM/glm.hpp>
//#include <GLM/GTC/matrix_transform.hpp>
//#include <GLM/GTC/type_ptr.hpp>
#include <iostream>
#include <Texture.h>

class player
{
public:
    bool IsAlive;
    int Lives;
    float Speed;
    std::unique_ptr<Texture> m_texture;

    void Shoot();
    void Move();
    void Die();
    void LoseLife();

};
//texture
//shoot
//cooldown
