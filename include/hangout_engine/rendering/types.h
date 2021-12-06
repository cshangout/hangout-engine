#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace HE {
    class Texture;

    struct Vertex {
        glm::vec3 position;
        glm::vec4 color {1.f, 1.f, 1.f, 1.f};
        glm::vec2 uv;
        glm::vec3 normal {0.f, 0.f, 0.f };
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

    struct AmbientLightSettings {
        glm::vec3 color;
        float intensity;
    };

    struct Light {
        glm::vec3 Position;
        glm::vec3 AmbientColor;
        glm::vec3 DiffuseColor;
        glm::vec3 SpecularColor;
    };

    struct SceneData {
        glm::mat4 ProjectionMatrix { 1.f };
        glm::mat4 ViewMatrix { 1.f };
        glm::vec3 ClearColor {0.25f, 0.25f, 0.25f};
        glm::vec3 CameraPosition {0.f, 0.f, 0.f};

        std::vector<Light> Lights {};
    };

    enum class ColorType {
        FLOAT,
        UNSIGNED_CHAR
    };
}
