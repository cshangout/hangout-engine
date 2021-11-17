#pragma once

#include <glm/glm.hpp>

namespace HE {
    class Camera {
    public:
        explicit Camera(glm::mat4 projectionMatrix);

        [[nodiscard]] const glm::vec3& GetPosition() const { return _position; }

        void SetPosition(const glm::vec3& position) {
            _position = position;
            recalculateViewMatrix();
        }


        [[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
        [[nodiscard]] const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
        [[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }

    protected:
        virtual void recalculateViewMatrix() { _viewProjectionMatrix = _projectionMatrix * _viewMatrix; };

    protected:
        glm::mat4 _projectionMatrix { 1.f };
        glm::mat4 _viewMatrix { 1.f };
        glm::mat4 _viewProjectionMatrix { 1.f };

        glm::vec3 _position {0, 0, -1};

    };

    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        explicit OrthographicCamera(float aspect);

        [[nodiscard]] float GetRotation() const  { return _rotation; }

        void SetRotation(float rotation) {
            _rotation = rotation;
            recalculateViewMatrix();
        }
    protected:
        void recalculateViewMatrix() override;
    private:
        float _rotation = 0.0f;
    };

    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(float fov, float aspect, float near, float far);

        void LookAt(const glm::vec3& lookAt);
    protected:
        void recalculateViewMatrix() override;
    };
}