#include <hangout_engine/core/components/camera_component.h>
#include <hangout_engine/service_locator.h>

namespace HE {

    glm::mat4 CameraComponent::GetProjectionMatrix() const {
        auto aspect = ServiceLocator::GetWindow()->GetAspectRatio();

        return _isPerspective ?
               glm::perspective(glm::radians(_fieldOfView), aspect, _near, _far) :
               glm::ortho(-aspect, aspect, -1.f, 1.f, _near, _far);
    }
}