#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw_gl3.h>
#include <GLM/glm.hpp>
#include <GLM/GTC/matrix_transform.hpp>
#include <GLM/GTC/type_ptr.hpp>
#define _USE_MATH_DEFINES 
#include <math.h>

#define TO_RADIANS(x) (float) (x * (M_PI / 180))

const GLint widht = 800;
const GLint heigth = 600;
#define WIDTH widht
#define HEIGHT heigth