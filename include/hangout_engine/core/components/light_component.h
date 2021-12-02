#pragma once

#include <glm/fwd.hpp>
#include "transform_component.h"

namespace HE {
    class LightComponent {
    public:
        LightComponent() = default;
        LightComponent(const LightComponent &) = default;

    private:
        char _privateValueJustToMakeItWork {0};
    };
}
