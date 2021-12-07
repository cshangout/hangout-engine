#pragma once

namespace HE {

    class SkyboxComponent {
    public:
        SkyboxComponent() = default;
        SkyboxComponent(const MeshComponent &) = default;

        void SetTexture(std::shared_ptr<Texture> texture);
    private:

        std::shared_ptr<Shader> _shader;
    };
}
