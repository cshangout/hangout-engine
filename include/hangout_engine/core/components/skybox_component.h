#pragma once

#include "mesh_component.h"
#include <hangout_engine/rendering/texture.h>

namespace HE {

    class SkyboxComponent : public MeshComponent {
    public:
        SkyboxComponent();
        SkyboxComponent(const SkyboxComponent &) = default;

        void SetTextureFace(TextureData& data, const TextureTarget target);
        void SetTextureFace(TextureData&& data, const TextureTarget target);
    private:
    };
}
