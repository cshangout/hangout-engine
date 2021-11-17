
#include "open_gl_buffer.h"
#include "open_gl_types.h"

namespace HE {

    /**
     *          VERTEX BUFFER
     */

    OpenGLVertexBuffer::OpenGLVertexBuffer() : _count(0) {
        glGenBuffers(1, &_handle);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &_handle);
    }

    void OpenGLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, _handle);
    }

    void OpenGLVertexBuffer::UploadData(const std::vector<Vertex>& vertices) {
        _count = vertices.size();
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(Vertex)),
                     vertices.data(), GL_STATIC_DRAW);
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
        _layout = layout;
    }

    const BufferLayout &OpenGLVertexBuffer::GetLayout() const {
        return _layout;
    }

    void OpenGLVertexBuffer::BindBufferLayout() {

        uint32_t index = 0;
        for (const auto& element : _layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE, _layout.GetStride(), (const void*)element.offset);
            index++;
        }
    }

    /**
     *          INDEX BUFFER
     */

    OpenGLIndexBuffer::OpenGLIndexBuffer() {
        glGenBuffers(1, &_handle);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &_handle);
    }

    void OpenGLIndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
    }

    void OpenGLIndexBuffer::UploadData(const std::vector<uint32_t> &indices) {
        _count = indices.size();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(uint32_t)),
                     indices.data(), GL_STATIC_DRAW);
    }

    uint32_t OpenGLIndexBuffer::GetCount() {
        return _count;
    }

}
