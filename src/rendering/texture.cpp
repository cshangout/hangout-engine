#include <hangout_engine/rendering/texture.h>
#include <hangout_engine/platform/filesystem.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <algorithm>
#include <iostream>

namespace HE {

    TextureData::TextureData(std::filesystem::path &&texturePath, bool flipVertical) : _width(0), _height(0), _channels(0) {
        Path textureAssetPath = Filesystem::GetAssetPath() /= texturePath;
        stbi_set_flip_vertically_on_load(flipVertical);

        _colorType = ColorType::UNSIGNED_CHAR;

        auto image = stbi_load(textureAssetPath.string().c_str(), &_width, &_height, &_channels, 0);
        _data.resize(_width * _height * _channels);

        memcpy(_data.data(), image, _width * _height * _channels);

        stbi_image_free(image);
    }

    TextureData::TextureData(uint32_t width, uint32_t height, glm::vec3 color) {
        _width = static_cast<int>(width);
        _height = static_cast<int>(height);
        _channels = 3;
        _colorType = ColorType::UNSIGNED_CHAR;

        _data.resize(_width * _height * _channels);

        for (uint32_t i = 0; i < width * height * _channels; i ++) {
            auto colorByte = static_cast<unsigned char>(color[i % 3] * 255.0);
            _data[i] = colorByte;
        }
    }

    TextureData::~TextureData() {
        _data.clear();
    }

    const unsigned char *TextureData::GetData() const {
        return _data.data();
    }

    std::pair<uint32_t, uint32_t> TextureData::GetSize() const {
        return {_width, _height};
    }

    int TextureData::GetChannels() const {
        return _channels;
    }


}