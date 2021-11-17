#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace HE {
    class Texture;

    struct Vertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
    };

    enum class TextureBindingIndex {
        Texture0 = 0,
        Texture1,
        Texture2,
        Normal,
        Roughness,
    };

    struct TextureSamplerBinding {
        std::string samplerName;
        TextureBindingIndex index;
        std::shared_ptr<Texture> texture;
    };

    enum class TextureWrapMode {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class TextureFiltering {
        Nearest,
        NearestMipMapNearest,
        NearestMiMapLinear,
        Linear,
        LinearMipMapNearest,
        LinearMipMapLinear
    };

    struct SamplerSettings {
        TextureWrapMode repeatModeS = TextureWrapMode::Repeat;
        TextureWrapMode repeatModeT = TextureWrapMode::Repeat;
        TextureFiltering minFilter = TextureFiltering::Linear;
        TextureFiltering magFilter = TextureFiltering::Linear;

        glm::vec4 borderColor {1.f, 0.f, 1.f, 1.f};
    };

    enum class ShaderDataType {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };
}