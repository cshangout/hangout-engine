#include <hangout_engine/rendering/texture.h>
#include <hangout_engine/platform/filesystem.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace HE {

    TextureData::TextureData(std::filesystem::path &&texturePath, bool flipVertical) : _width(0), _height(0), _channels(0) {
        Path textureAssetPath = Filesystem::GetAssetPath() /= texturePath;
        stbi_set_flip_vertically_on_load(flipVertical);
        _data = stbi_load(textureAssetPath.string().c_str(), &_width, &_height, &_channels, 0);
    }

    TextureData::~TextureData() {
        if (_data) {
            stbi_image_free(_data);
        }
    }

    const unsigned char *TextureData::GetData() const {
        return _data;
    }

    std::pair<uint32_t, uint32_t> TextureData::GetSize() const {
        return {_width, _height};
    }

    int TextureData::GetChannels() const {
        return _channels;
    }

}