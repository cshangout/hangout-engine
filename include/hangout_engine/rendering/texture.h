#pragma once
#include <filesystem>
#include "types.h"

namespace HE {
    struct TextureData {
        TextureData(std::filesystem::path&& texturePath, bool flipVertical = false);

        ~TextureData();

        [[nodiscard]] std::pair<uint32_t, uint32_t> GetSize() const;
        [[nodiscard]] const unsigned char* GetData() const;
        [[nodiscard]] int GetChannels() const;

    private:
        int _width;
        int _height;
        int _channels;
        unsigned char* _data = nullptr;

    };

    class Texture {
    public:
        ~Texture() = default;

        virtual void Bind() = 0;
        virtual void BindSamplerSettings(const SamplerSettings& settings) = 0;
        virtual void UploadData(const TextureData& data) = 0;
    };
}