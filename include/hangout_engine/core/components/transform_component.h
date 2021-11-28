#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace HE {
    class TransformComponent {
    public:
        TransformComponent() = default;

        TransformComponent(const TransformComponent &) = default;

        const glm::vec3& GetPosition() { return _position; }
        void SetPosition(const glm::vec3 position) {
            _position = position;
        }

        const glm::vec3& GetScale() { return _scale; }
        void SetScale(const glm::vec3 scale) {
            _scale = scale;
        }

        const glm::vec3& GetRotation() { return _rotation; }
        void SetRotation(const glm::vec3 rotation) {
            _rotation = rotation;
        }

        [[nodiscard]] glm::mat4 GetTransform() const {
            glm::mat4 transform {1.f};
            transform = glm::translate(transform, _position);
            transform = glm::scale(transform, _scale);

            auto rotation = glm::eulerAngleXYZ(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));
            transform *= rotation;

            return transform;
        }

    private:
        glm::vec3 _position {};
        glm::vec3 _scale {1.f, 1.f, 1.f};
        glm::vec3 _rotation {0.f, 0.f, 0.f};
    };
}