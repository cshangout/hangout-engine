#include <hangout_engine/rendering/camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace HE {
    Camera::Camera(glm::mat4 projectionMatrix) : _projectionMatrix(projectionMatrix){
        Camera::recalculateViewMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : Camera(glm::ortho(left, right, bottom, top, -1.f, 1.f)){
        OrthographicCamera::recalculateViewMatrix();
    }

    OrthographicCamera::OrthographicCamera(float aspect)
            : Camera(glm::ortho(-aspect, aspect, -1.f, 1.f, -1.f, 1.f)) {
        OrthographicCamera::recalculateViewMatrix();
    }

    void OrthographicCamera::recalculateViewMatrix() {
        glm::mat4 translation = glm::translate(glm::mat4{1.f}, _position);
        glm::mat4 rotation = glm::rotate(glm::mat4{1.f}, glm::radians(_rotation), glm::vec3(0, 0, 1.f));

        glm::mat4 transform = translation * rotation;

        _viewMatrix = glm::inverse(transform);
        Camera::recalculateViewMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
        : Camera(glm::perspective(glm::radians(fov), aspect, near, far)){

    }

    void PerspectiveCamera::recalculateViewMatrix() {
        Camera::recalculateViewMatrix();
    }

    void PerspectiveCamera::LookAt(const glm::vec3& lookAt) {
        _viewMatrix = glm::lookAt(
            _position,
            lookAt,
            glm::vec3(0.f, 1.f, 0.f)
        );

        recalculateViewMatrix();
    }
}