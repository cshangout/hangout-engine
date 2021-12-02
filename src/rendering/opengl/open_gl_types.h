#pragma once
#include "open_gl_graphics.h"
#include <hangout_engine/rendering/types.h>
#include <iostream>

namespace HE {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
                return 0;
        }
    }

    static GLint TextureWrapModeToOpenGL(TextureWrapMode mode) {
        switch (mode) {
            case TextureWrapMode::Repeat:
                return GL_REPEAT;
            case TextureWrapMode::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case TextureWrapMode::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
            case TextureWrapMode::ClampToBorder:
#ifdef GLES
                std::cout << "WARNING: Clamp to border is not supported in GLES3.0. Using Clamp To Edge instead." << std::endl;
                return GL_CLAMP_TO_EDGE;
#else
                return GL_CLAMP_TO_BORDER;
#endif
        }
    }

    static GLint TextureFilteringToOpenGL(TextureFiltering filtering) {
        switch(filtering){
            case TextureFiltering::Nearest:
                return GL_NEAREST;
            case TextureFiltering::NearestMipMapNearest:
                return GL_NEAREST_MIPMAP_NEAREST;
            case TextureFiltering::NearestMiMapLinear:
                return GL_NEAREST_MIPMAP_LINEAR;
            case TextureFiltering::Linear:
                return GL_LINEAR;
            case TextureFiltering::LinearMipMapNearest:
                return GL_LINEAR_MIPMAP_NEAREST;
            case TextureFiltering::LinearMipMapLinear:
                return GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    static GLint TextureChannelNumberToOpenGL(int channels) {
        switch(channels) {
            case 3:
                return GL_RGB;
            case 4:
                return GL_RGBA;
            default:
                assert(true && "Number of channels not supported!");
                return 0;
        }
    }

    static GLint ColorTypeToOpenGL(ColorType colorType) {
        switch(colorType) {
            case ColorType::FLOAT:
                return GL_FLOAT;
                break;
            case ColorType::UNSIGNED_CHAR:
                return GL_UNSIGNED_BYTE;
                break;
            default:
                return 0;
        }
    }
}
