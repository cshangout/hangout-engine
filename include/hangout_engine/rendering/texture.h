#pragma once
#include <filesystem>
#include "types.h"

namespace HE {


    struct TextureData {
        TextureData(std::filesystem::path&& texturePath, bool flipVertical = false);
        TextureData(uint32_t width, uint32_t height, glm::vec3 color = {1.f, 1.f, 1.f});

        ~TextureData();

        [[nodiscard]] std::pair<uint32_t, uint32_t> GetSize() const;
        [[nodiscard]] const unsigned char* GetData() const;
        [[nodiscard]] int GetChannels() const;
        [[nodiscard]] ColorType GetColorType() const { return _colorType; }
    private:
        int _width;
        int _height;
        int _channels;

        uint32_t _textureSize { 0 };

        ColorType _colorType;

        std::vector<unsigned char> _data;

    };

    class Texture {
    public:
        explicit Texture(TextureType type) : _type(type) {};
        ~Texture() = default;

        virtual void Bind() = 0;
        virtual void BindSamplerSettings(const SamplerSettings& settings) = 0;
        virtual void UploadData(const TextureData& data, TextureTarget target) = 0;
        virtual void UploadData(const TextureData&& data, TextureTarget target) = 0;

        [[nodiscard]] std::pair<uint32_t, uint32_t> GetSize() const;

        [[nodiscard]] TextureType GetType() const { return _type; }
    protected:
        TextureType _type;
        int _width { 0 };
        int _height { 0 };
    };
}