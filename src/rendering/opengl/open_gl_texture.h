#pragma once

#include <hangout_engine/rendering/texture.h>
#include <hangout_engine/rendering/types.h>
#include "open_gl_graphics.h"

namespace HE {
    class OpenGLTexture : public Texture {
    public:
        OpenGLTexture();
        ~OpenGLTexture();

        void Bind() override;
        void BindSamplerSettings(const SamplerSettings& settings) override;
        void UploadData(const std::shared_ptr<TextureData>& data) override;

    private:
        uint32_t _handle;
    };
}


