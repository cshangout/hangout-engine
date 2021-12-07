#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <hangout_engine/rendering/types.h>
#include <hangout_engine/rendering/vertex_array.h>
#include <hangout_engine/rendering/shader.h>

namespace HE {
    struct Material {
        glm::vec3 Ambient {1.f, 1.f, 1.f };
        glm::vec3 Diffuse {1.f, 1.f, 1.f };
        glm::vec3 Specular {1.f, 1.f, 1.f };

        float Shininess {32.f };
    };

    class MeshComponent {
    public:
        MeshComponent() = delete;
        MeshComponent(const MeshComponent &) = default;

        explicit MeshComponent(std::vector<Vertex> &&vertices, std::vector<uint32_t> &&indices, const BufferLayout&& layout = {
                {HE::ShaderDataType::Float3, "aPos"},
                {HE::ShaderDataType::Float4, "aColor"},
                {HE::ShaderDataType::Float2, "aTexCoord"},
                {HE::ShaderDataType::Float3, "aNormal"},
        });

        [[nodiscard]] std::weak_ptr<VertexArray> GetVertexArray() const { return _vao; }

        [[nodiscard]] std::weak_ptr<Shader> GetShader() const { return _shader; }
        void SetShader(std::shared_ptr<Shader> shader) { _shader = shader; };

        Material Mat {};

    private:
        std::shared_ptr<Shader> _shader;
        std::shared_ptr<VertexArray> _vao = nullptr;
    };
}