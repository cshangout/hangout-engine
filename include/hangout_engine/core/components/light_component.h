#pragma once

#include <glm/fwd.hpp>
#include "transform_component.h"

namespace HE {
    class LightComponent {
    public:
        LightComponent() = default;
        LightComponent(const LightComponent &) = default;

        glm::vec3 AmbientColor { 0.2f, 0.2f, 0.2f };
        glm::vec3 DiffuseColor { 0.5f, 0.5f, 0.5f };
        glm::vec3 SpecularColor { 1.f, 1.f, 1.f };
    };
}
