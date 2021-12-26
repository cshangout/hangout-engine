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
            mesh_ptr->Bind();

            shader_ptr->UniformMat4("u_model", transform.GetTransform());
            shader_ptr->UniformMat4("u_inverseNormal", glm::inverse(transform.GetTransform()));

            auto addedSampler = false;
            auto samplers = shader_ptr->GetTextureSamplers();
            auto diffuseSampler = std::find_if(samplers.begin(), samplers.end(), [](auto& sampler) {
                return sampler.samplerName == "material.diffuse";
            });

            if (diffuseSampler == samplers.end() && mesh.Mat.DiffuseTexture != nullptr) {
                std::cout << "Attaching diffuse texture to shader" << std::endl;
                samplers.emplace_back(
                        TextureSamplerBinding {
                                .samplerName = "material.diffuse",
                                .index = TextureBindingIndex::Diffuse,
                                .texture = mesh.Mat.DiffuseTexture
                        }
                );

                addedSampler = true;
            }

            auto specularSampler = std::find_if(samplers.begin(), samplers.end(), [](auto& sampler) {
                return sampler.samplerName == "material.specular";
            });

            if (specularSampler == samplers.end() && mesh.Mat.SpecularTexture != nullptr) {
                std::cout << "Attaching specular texture to shader" << std::endl;
                samplers.emplace_back(
                        TextureSamplerBinding {
                                .samplerName = "material.specular",
                                .index = TextureBindingIndex::Specular,
                                .texture = mesh.Mat.SpecularTexture
                        }
                );

                addedSampler = true;
            }

            if (addedSampler) shader_ptr->SetTextureSamplers(std::move(samplers));

            shader_ptr->Float("material.shininess", mesh.Mat.Shininess);

            DrawIndexed(mesh_ptr);
        }
    }
}