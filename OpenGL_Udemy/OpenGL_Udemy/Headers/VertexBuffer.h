#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <OpenGLDebugger.h>

#include <iostream>

class VertexBuffer 
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_VertexBufferID;
};