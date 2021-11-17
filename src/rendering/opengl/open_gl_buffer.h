#pragma once
#include <hangout_engine/rendering/buffer.h>
#include "open_gl_graphics.h"

namespace HE {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer();
        ~OpenGLVertexBuffer();
        void Bind() override;

        void UploadData(const std::vector<Vertex>& vertices) override;
        void SetLayout(const BufferLayout& layout) override;
        const BufferLayout& GetLayout() const override;
        void BindBufferLayout() override;
        uint32_t GetCount() override { return _count; };

    private:
        BufferLayout _layout;
        uint32_t _count = 0;
        uint32_t _handle = 0;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer();
        ~OpenGLIndexBuffer();
        void Bind() override;

        void UploadData(const std::vector<uint32_t> &vector) override;

        uint32_t GetCount() override;
    private:
        uint32_t _count = 0;
        uint32_t _handle = 0;

    };
}
