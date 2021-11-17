#pragma once

#include "buffer.h"
#include <memory>

namespace HE {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
        virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;
    private:
    };
}