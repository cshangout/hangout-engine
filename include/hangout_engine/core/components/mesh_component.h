#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <hangout_engine/rendering/types.h>
#include <hangout_engine/rendering/vertex_array.h>
#include <hangout_engine/rendering/shader.h>

namespace HE {
    class MeshComponent {
    public:
        MeshComponent() = default;

        MeshComponent(const MeshComponent &) = default;

        explicit MeshComponent(std::vector<Vertex> &&vertices, std::vector<uint32_t> &&indices);

        [[nodiscard]] std::weak_ptr<VertexArray> GetVertexArray() const { return _vao; }

        [[nodiscard]] std::weak_ptr<Shader> GetShader() const { return _shader; }
        void SetShader(std::shared_ptr<Shader> shader);

    private:
        std::shared_ptr<Shader> _shader;
        std::shared_ptr<VertexArray> _vao = nullptr;
    };
}