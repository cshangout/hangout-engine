#include "open_gl_vertex_array.h"
#include "open_gl_graphics.h"

namespace HE {
    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &_handle);
    }

    OpenGLVertexArray::~OpenGLVertexArray() = default;

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(_handle);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
        Bind();
        vertexBuffer->Bind();
        vertexBuffer->BindBufferLayout();

        _vertexBuffers.push_back(vertexBuffer);
        Unbind();
    }

    void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
        Bind();
        indexBuffer->Bind();
        _indexBuffer = indexBuffer;
    }

    const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() {
        return _indexBuffer;
    }

}