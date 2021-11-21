#include <hangout_engine/rendering/camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <hangout_engine/service_locator.h>

namespace HE {
    Camera::Camera(
            glm::vec3 position,
            glm::vec3 up,
            float yaw,
            float pitch,
            float near,
            float far,
            bool isPerspective,
            float fieldOfView)
        : _position(position), _up(up), _yaw(yaw), _pitch(pitch), _near(near), _far(far), _isPerspective(isPerspective), _fieldOfView(fieldOfView), _worldUp(up){

        Camera::recalculateCameraVectors();
    }

    void Camera::recalculateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(front);

        // also re-calculate the Right and Up vector
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up    = glm::normalize(glm::cross(_right, _front));
    }

    void Camera::Translate(Camera::MoveDirection direction, float amount) {
        switch (direction) {
            case MoveDirection::Forward:
                _position += _front * amount;
                break;
            case MoveDirection::Backward:
                _position -= _front * amount;
                break;
            case MoveDirection::Left:
                _position -= _right * amount;
                break;
            case MoveDirection::Right:
                _position += _right * amount;
                break;
            case MoveDirection::Up:
                _position += _up * amount;
                break;
            case MoveDirection::Down:
                _position -= _up * amount;
                break;
            default:
                break;
        }
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        auto aspect = HE::ServiceLocator::GetWindow()->GetAspectRatio();

        return _isPerspective ?
            glm::perspective(glm::radians(_fieldOfView), aspect, _near, _far) :
            glm::ortho(-aspect, aspect, -1.f, 1.f, _near, _far);
    }

    const glm::mat4 &Camera::GetViewMatrix() const {
        return glm::lookAt(_position, _position + _front, _up);
    }

    void Camera::RotateBy(float xAmount, float yAmount, bool constrainPitch) {
        _yaw += xAmount;
        _pitch += yAmount;

        if (constrainPitch) {
            _pitch = std::clamp(_pitch, -89.f, 89.f);
        }

        recalculateCameraVectors();
    }

}