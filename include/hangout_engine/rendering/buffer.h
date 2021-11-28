#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <cassert>

#include "types.h"

namespace HE {
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::None:
                assert(false && "None ShaderDataType Requested");
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 8;
            case ShaderDataType::Float3:
                return 12;
            case ShaderDataType::Float4:
                return 16;
            case ShaderDataType::Mat3:
                return 36;
            case ShaderDataType::Mat4:
                return 48;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 8;
            case ShaderDataType::Int3:
                return 12;
            case ShaderDataType::Int4:
                return 16;
            case ShaderDataType::Bool:
                return 1;
        }
        assert(false && "Invalid ShaderDataType requested");
        return 0;
    }

    struct BufferElement {
        ShaderDataType type;
        std::string name;
        uint32_t offset;
        uint32_t size;
        bool normalized;

        BufferElement(ShaderDataType type, std::string name, bool normalized = false)
            : name(std::move(name)), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {

        }

        [[nodiscard]] uint32_t GetComponentCount() const {
            switch(type) {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 9;
                case ShaderDataType::Mat4:
                    return 16;
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
                case ShaderDataType::None:
                    assert(false && "None ShaderDataType Requested");
            }
            assert(false && "Invalid ShaderDataType Requested");
            return -1;
        }
    };

    class BufferLayout {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements) : _elements{ elements } {
            calculateOffsetsAndStride();
        }

        BufferLayout() : _elements{} {}

        [[nodiscard]] inline const std::vector<BufferElement>& GetElements() const { return _elements; }
        [[nodiscard]] inline uint32_t GetStride() const { return _stride; }

        std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
        std::vector<BufferElement>::iterator end() { return _elements.end(); }
    private:
        void calculateOffsetsAndStride() {
            uint32_t offset = 0;
            _stride = 0;
            for (auto& element : _elements) {
                element.offset = offset;
                offset += element.size;
                _stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> _elements;
        uint32_t _stride = 0;
    };

    class VertexBuffer {
    public:
        virtual void Bind() = 0;
        virtual void UploadData(const std::vector<Vertex>&) = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        [[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;
        virtual uint32_t GetCount() = 0;
        virtual void BindBufferLayout() = 0;

    };

    class IndexBuffer {
    public:
        ~IndexBuffer() = default;
        virtual void Bind() = 0;
        virtual void UploadData(const std::vector<uint32_t>&) = 0;
        virtual uint32_t GetCount() = 0;
    };
}