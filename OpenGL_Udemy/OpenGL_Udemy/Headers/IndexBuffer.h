#pragma once
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <Definitions.h>
#include <OpenGLDebugger.h>

#include <iostream>

class IndexBuffer
{
public:
    IndexBuffer(const void* data, unsigned int size);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
private:
    unsigned int m_IndexBufferID;
    unsigned int m_Count;
};