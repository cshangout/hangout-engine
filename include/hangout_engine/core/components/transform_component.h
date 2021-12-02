#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <algorithm>

namespace HE {
    enum class MoveDirection {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down
    };

    class TransformComponent {
    public:
        TransformComponent() = default;

        TransformComponent(const TransformComponent &) = default;

        const glm::vec3& GetPosition() { return _position; }
        void SetPosition(const glm::vec3 position) {
            _position = position;
            recalculateTransform();
        }

        const glm::vec3& GetScale() { return _scale; }
        void SetScale(const glm::vec3 scale) {
            _scale = scale;
            recalculateTransform();
        }

        const glm::vec3& GetRotation() { return _rotation; }
        void SetRotation(const glm::vec3 rotation) {
            _rotation = rotation;
            recalculateTransform();
        }

        void Translate(MoveDirection direction, float amount) {
            auto rotation =
                    glm::yawPitchRoll(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));

            glm::vec3 forwardVector = {rotation[2]};
            glm::vec3 upVector = {rotation[1]};
            glm::vec3 rightVector = {rotation[0]};

            switch (direction) {
                case MoveDirection::Forward:
                    _position += forwardVector * amount;
                    break;
                case MoveDirection::Backward:
                    _position -= forwardVector * amount;
                    break;
                case MoveDirection::Left:
                    _position -= rightVector * amount;
                    break;
                case MoveDirection::Right:
                    _position += rightVector * amount;
                    break;
                case MoveDirection::Up:
                    _position += upVector * amount;
                    break;
                case MoveDirection::Down:
                    _position -= upVector * amount;
                    break;
                default:
                    break;
            }
            recalculateTransform();
        }

        void RotateBy(float xAmount, float yAmount = 0.f, float zAmount = 0.f, bool constrainPitch = false) {

            _rotation.x += xAmount;
            _rotation.y += yAmount;
            _rotation.z += zAmount;

            if (constrainPitch) {
                _rotation.y = std::clamp(_rotation.y, -89.f, 89.f);
            }
            recalculateTransform();
        }

        [[nodiscard]] glm::mat4 GetTransform() const {
            return _transform;
        }

    private:
        glm::vec3 _position {};
        glm::vec3 _scale {1.f, 1.f, 1.f};
        glm::vec3 _rotation {0.f, 0.f, 0.f};

        glm::mat4 _transform {};

        void recalculateTransform() {
            _transform = glm::mat4{1.f};
            _transform = glm::translate(_transform, _position);
            auto rotation = glm::yawPitchRoll(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));
            _transform *= rotation;
            _transform = glm::scale(_transform, _scale);
        }
    };
}