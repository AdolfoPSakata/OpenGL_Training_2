#include <Renderer.h>

void Renderer::Clear() const
{
    DebugLog(glClearColor(0,0.3f,0,1));
    DebugLog(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const RendererObject* rendererObject)
{
    rendererObject->vao->Bind();
    rendererObject->vbu->Bind();
    rendererObject->ibo->Bind();
    rendererObject->shader->Bind();

    DebugLog(glDrawElements(GL_TRIANGLES, rendererObject->ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Unbind(const RendererObject* rendererObject)
{
    rendererObject->vao->Unbind();
    rendererObject->vbu->Unbind();
    rendererObject->ibo->Unbind();
    rendererObject->shader->Unbind();
}