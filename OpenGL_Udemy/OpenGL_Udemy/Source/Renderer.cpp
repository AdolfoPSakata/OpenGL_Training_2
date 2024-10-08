#include <Renderer.h>

#define SetUniform(x) (GLEW_GET_FUN(x))

void Renderer::Clear() const
{
    DebugLog(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const RendererObject& renderObject)
{
    renderObject.vao.Bind();
    renderObject.vbu.Bind();
    renderObject.ibu.Bind();
    renderObject.shader.Bind();

    DebugLog(glDrawElements(GL_TRIANGLES, renderObject.ibu.GetCount(), GL_UNSIGNED_INT, nullptr));
}

//TODO: move to class
int Renderer::GetUniformLocation(const int shader, const char* uniformString)
{
    int location = glGetUniformLocation(shader, SetUniform(uniformString));
    return location;
}

void Renderer::Unbind(const RendererObject& renderObject)
{
    renderObject.vao.Unbind();
    renderObject.vbu.Unbind();
    renderObject.ibu.Unbind();
    renderObject.shader.Unbind();
}