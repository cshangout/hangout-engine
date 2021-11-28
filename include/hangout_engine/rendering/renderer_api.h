#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <hangout_engine/core/components/mesh_component.h>
#include <hangout_engine/core/components/transform_component.h>
#include "vertex_array.h"

namespace HE {
    class RendererAPI {
    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawMesh(const MeshComponent&, const TransformComponent&) = 0;
        virtual void DrawArray(const std::shared_ptr<VertexArray>&) = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) = 0;
    };
}