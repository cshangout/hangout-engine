#pragma once

#include <glm/fwd.hpp>
#include "transform_component.h"

namespace HE {
    class CameraComponent {
    public:
        CameraComponent() = default;
        CameraComponent(const CameraComponent &) = default;

        void SetIsPerspective(bool isPerspective) { _isPerspective = isPerspective; }
        [[nodiscard]] bool IsPerspective() const { return _isPerspective; }

        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        bool IsActive() const { return _isActive; }

    private:
        float _fieldOfView { 45.f };
        float _near { 0.001f };
        float _far { 1000.f };
        bool _isPerspective { true };
        bool _isActive { true };
    };
}
