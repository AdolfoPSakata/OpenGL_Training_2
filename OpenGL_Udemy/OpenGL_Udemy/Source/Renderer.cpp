#include <Renderer.h>

void Renderer::Clear() const
{
    DebugLog(glClearColor(0,0.3f,0,1));
    DebugLog(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const RendererObject& renderObject)
{
    renderObject.vao.Bind();
    renderObject.vbu.Bind();
    renderObject.ibo.Bind();
    renderObject.shader.Bind();

    //glDrawArrays(GL_TRIANGLES, 0,3);
    DebugLog(glDrawElements(GL_TRIANGLES, renderObject.ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Unbind(const RendererObject& renderObject)
{
    renderObject.vao.Unbind();
    renderObject.vbu.Unbind();
    renderObject.ibo.Unbind();
    renderObject.shader.Unbind();
}