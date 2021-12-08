#pragma once

#include <hangout_engine/rendering/texture.h>
#include <hangout_engine/rendering/types.h>
#include "open_gl_graphics.h"

namespace HE {
    class OpenGLTexture : public Texture {
    public:
        explicit OpenGLTexture(TextureType type = TextureType::TWOD);
        ~OpenGLTexture();

        void Bind() override;
        void BindSamplerSettings(const SamplerSettings& settings) override;
        void UploadData(const TextureData& data, TextureTarget target) override;
        void UploadData(const TextureData&& data, TextureTarget target) override;
        uint32_t GetHandle() const override { return _handle; }

    private:
        uint32_t _handle;
    };
}


