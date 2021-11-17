#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "vertex_array.h"

namespace HE {
    class RendererAPI {
    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawArray(const std::shared_ptr<VertexArray>&) = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) = 0;
    };
}