#include <glm/gtc/type_ptr.hpp>
#include "open_gl_texture.h"
#include "open_gl_types.h"

namespace HE {
    OpenGLTexture::OpenGLTexture(TextureType type) : _handle(0), Texture(type) {
        glGenTextures(1, &_handle);
    }

    OpenGLTexture::~OpenGLTexture() {
        if (_handle) {
            glDeleteTextures(1, &_handle);
            std::cout << "Texture being destroyed." << std::endl;
        }
    }

    void OpenGLTexture::Bind() {
        if (_handle) {
            auto type = TextureTypeToOpenGL(_type);
            glBindTexture(type, _handle);
        }
    }

    void OpenGLTexture::BindSamplerSettings(const SamplerSettings& settings) {
        glTexParameteri(TextureTypeToOpenGL(_type), GL_TEXTURE_WRAP_S, TextureWrapModeToOpenGL(settings.repeatModeS));
        glTexParameteri(TextureTypeToOpenGL(_type), GL_TEXTURE_WRAP_T, TextureWrapModeToOpenGL(settings.repeatModeT));
        if (_type == TextureType::CUBEMAP) {
            glTexParameteri(TextureTypeToOpenGL(_type), GL_TEXTURE_WRAP_R, TextureWrapModeToOpenGL(settings.repeatModeT));
        }

#ifndef GLES
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(settings.borderColor));
#endif

        glTexParameteri(TextureTypeToOpenGL(_type), GL_TEXTURE_MIN_FILTER, TextureFilteringToOpenGL(settings.minFilter));
        glTexParameteri(TextureTypeToOpenGL(_type), GL_TEXTURE_MAG_FILTER, TextureFilteringToOpenGL(settings.magFilter));
    }

    void OpenGLTexture::UploadData(const TextureData& data, TextureTarget target) {
        assert(
            (_type == TextureType::TWOD && target == TextureTarget::TWOD) ||
            (_type == TextureType::CUBEMAP) && target != TextureTarget::TWOD &&
            "Target not valid for texture type."
        );

        auto [width, height] = data.GetSize();

        // If the texture size has changed (or is not initialized), allocate the space for it
        if (_width != width || _height != height) {
            std::vector<TextureTarget> targets {};

            if (_type == TextureType::TWOD) targets.emplace_back(TextureTarget::TWOD);
            else if (_type == TextureType::CUBEMAP) {
                assert(width == height && "Cubemap faces need to be square!");
                // on cubemaps, we need to allocate all faces
                targets.emplace_back(TextureTarget::CUBEMAP_POS_X);
                targets.emplace_back(TextureTarget::CUBEMAP_NEG_X);
                targets.emplace_back(TextureTarget::CUBEMAP_POS_Y);
                targets.emplace_back(TextureTarget::CUBEMAP_NEG_Y);
                targets.emplace_back(TextureTarget::CUBEMAP_POS_Z);
                targets.emplace_back(TextureTarget::CUBEMAP_NEG_Z);
            }

            for (auto allocateTarget : targets) {
                glTexImage2D(
                        TextureTargetToOpenGL(allocateTarget),
                        0,
                        TextureChannelNumberToOpenGL(data.GetChannels()),
                        static_cast<GLsizei>(width), static_cast<GLsizei>(height),
                        0,
                        TextureChannelNumberToOpenGL(data.GetChannels()),
                        GL_UNSIGNED_BYTE,
                        nullptr
                );
            }

            _width = static_cast<int>(width);
            _height = static_cast<int>(height);
        }

        glTexSubImage2D(
          TextureTargetToOpenGL(target),
          0,
          0, 0,
          static_cast<GLsizei>(width), static_cast<GLsizei>(height),
          TextureChannelNumberToOpenGL(data.GetChannels()),
          GL_UNSIGNED_BYTE,
          data.GetData()
        );

        glGenerateMipmap(TextureTypeToOpenGL(_type));
    }

    void OpenGLTexture::UploadData(const TextureData&& data, TextureTarget target) {
        auto theData = data;
        UploadData(theData, target);
    }
}