#include <hangout_engine/core/scene.h>
#include <hangout_engine/core/entity.h>
#include <hangout_engine/service_locator.h>
#include <hangout_engine/core/components/transform_component.h>
#include <hangout_engine/core/components/mesh_component.h>
#include <hangout_engine/rendering/render_command.h>
#include <hangout_engine/core/components/camera_component.h>
#include "hangout_engine/core/components/light_component.h"

namespace HE {
    Scene::Scene() {}

    Scene::~Scene() {
        _entities.clear();
    }

    Entity *Scene::CreateEntity() {
        _entities.push_back(std::make_unique<Entity>(_registry));
        return _entities[_entities.size() - 1].get();
    }

    void Scene::Update() {

    }

    void Scene::Render() {
        // TODO: Get active camera
        RenderCommand::SetClearColor(glm::vec4{_sceneData.ClearColor, 1.f});
        RenderCommand::Clear();

        auto lightGroup = _registry.group<LightComponent>(entt::get<TransformComponent>);

        for (auto entity : lightGroup) {
            auto transform = lightGroup.get<TransformComponent>(entity);

            _sceneData.LightPosition = transform.GetPosition();
        }

        auto cameraGroup = _registry.group<CameraComponent>(entt::get<TransformComponent>);

        for (auto entity : cameraGroup) {
            auto [transform, camera] = cameraGroup.get<TransformComponent, CameraComponent>(entity);

            if (camera.IsActive()) {
                _sceneData.ProjectionMatrix = camera.GetProjectionMatrix();
                _sceneData.ViewMatrix = glm::inverse(transform.GetTransform());
                break;
            }
        }

        ServiceLocator::GetRenderer()->BeginScene();

        // Draw the objects
        uint32_t lastShaderHandle = 0;
        auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>);

        for (auto entity : group) {
            auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

            auto shader_ptr = mesh.GetShader().lock();
            if (shader_ptr && lastShaderHandle != shader_ptr->GetHandle()) {
                shader_ptr->Bind();
                lastShaderHandle = shader_ptr->GetHandle();
            }

            shader_ptr->Float3("ambientColor", _sceneData.AmbientSettings.color);
            shader_ptr->Float("ambientIntensity", _sceneData.AmbientSettings.intensity);
            shader_ptr->Float3("lightPosition", _sceneData.LightPosition);

            shader_ptr->UniformMat4("u_projection", _sceneData.ProjectionMatrix);
            shader_ptr->UniformMat4("u_view", _sceneData.ViewMatrix);

            RenderCommand::DrawMesh(mesh, transform);
        }

        ServiceLocator::GetRenderer()->EndScene();
    }

    void Scene::RemoveEntity(Entity *entity) {
        int entityIndex = -1;

        for (size_t i = 0; i < _entities.size(); i++) {
            if (_entities[i]->GetId() == entity->GetId()) {
                entityIndex = i;
                break;
            }
        }

        if (entityIndex != -1) {
            // this should clear the unique ptr, calling the destructor on the component -- which will remove itself from the registry.
            _entities.erase(_entities.begin() + entityIndex);
        }
    }
}