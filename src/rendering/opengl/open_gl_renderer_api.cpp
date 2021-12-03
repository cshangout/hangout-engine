#include "open_gl_renderer_api.h"
#include "open_gl_graphics.h"

namespace HE {

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawArray(const std::shared_ptr<VertexArray> &ptr) {
        for(const auto& vb : ptr->GetVertexBuffers()) {
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vb->GetCount()));
        }
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vao) {
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
    }

    void OpenGLRendererAPI::DrawMesh(const MeshComponent &mesh, const TransformComponent &transform) {
        auto shader_ptr = mesh.GetShader().lock();
        auto mesh_ptr = mesh.GetVertexArray().lock();
        if (shader_ptr && mesh_ptr) {
            shader_ptr->UniformMat4("u_model", transform.GetTransform());
            shader_ptr->UniformMat4("u_inverseNormal", glm::inverse(transform.GetTransform()));

            mesh_ptr->Bind();
            DrawIndexed(mesh_ptr);
        }
    }
}