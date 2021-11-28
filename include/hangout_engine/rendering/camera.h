#pragma once

#include <glm/glm.hpp>

namespace HE {
    class Camera {
    public:
        explicit Camera(
                glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = -90.f,
                float pitch = 0.f,
                float near = 0.01f,
                float far = 1000.f,
                bool isPerspective = true,
                float fieldOfView = 45.f);

        [[nodiscard]] const glm::vec3& GetPosition() const { return _position; }

        void SetPosition(const glm::vec3& position) {
            _position = position;
            recalculateCameraVectors();
        }

        void SetIsPerspective(bool isPerspective) { _isPerspective = isPerspective;
            recalculateCameraVectors(); }
        [[nodiscard]] bool IsPerspective() const { return _isPerspective; }

        // TODO: These transform operations should be moved into a generic Transform class later
        enum class MoveDirection {
            Forward,
            Backward,
            Left,
            Right,
            Up,
            Down
        };

        void Translate(MoveDirection direction, float amount);
        void RotateBy(float xAmount, float yAmount, bool constrainPitch = true);


        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
        [[nodiscard]] const glm::mat4 GetViewMatrix() const;

    private:
        void recalculateCameraVectors();

    private:
        glm::mat4 _viewMatrix { 1.f };

        glm::vec3 _position;
        glm::vec3 _up;
        glm::vec3 _right;
        float _yaw;
        float _pitch;
        float _zoom;
        glm::vec3 _front;

        float _fieldOfView { 45.f };
        float _near { 0.001f };
        float _far { 1000.f };
        bool _isPerspective { false };
        glm::vec3 _worldUp;

    };
}