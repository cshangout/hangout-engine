#include <glm/gtc/type_ptr.hpp>
#include "open_gl_texture.h"
#include "open_gl_types.h"

namespace HE {
    OpenGLTexture::OpenGLTexture() : _handle(0) {
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
            glBindTexture(GL_TEXTURE_2D, _handle);
        }
    }

    void OpenGLTexture::BindSamplerSettings(const SamplerSettings& settings) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapModeToOpenGL(settings.repeatModeS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapModeToOpenGL(settings.repeatModeT));

#ifndef GLES
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(settings.borderColor));
#endif

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilteringToOpenGL(settings.minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilteringToOpenGL(settings.magFilter));
    }

    void OpenGLTexture::UploadData(std::shared_ptr<TextureData> data) {
        auto [width, height] = data->GetSize();

        glTexImage2D(GL_TEXTURE_2D, 0, TextureChannelNumberToOpenGL(data->GetChannels()), static_cast<GLsizei>(width), static_cast<GLsizei>(height),
                     0, TextureChannelNumberToOpenGL(data->GetChannels()), GL_UNSIGNED_BYTE, data->GetData());

        glGenerateMipmap(GL_TEXTURE_2D);
    }

}