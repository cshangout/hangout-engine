#include <hangout_engine/core/scene.h>
#include <hangout_engine/core/entity.h>
#include <hangout_engine/service_locator.h>
#include <hangout_engine/core/components/transform_component.h>
#include <hangout_engine/core/components/mesh_component.h>
#include <hangout_engine/rendering/render_command.h>
#include <hangout_engine/core/components/camera_component.h>
#include <hangout_engine/core/components/light_component.h>
#include <hangout_engine/core/components/skybox_component.h>
#include "../rendering/opengl/open_gl_graphics.h"

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
        _sceneData.Lights.clear();

        RenderCommand::SetClearColor(glm::vec4{_sceneData.ClearColor, 1.f});
        RenderCommand::Clear();

        auto lightGroup = _registry.group<LightComponent>(entt::get<TransformComponent>);

        for (auto entity : lightGroup) {
            auto [transform, light] = lightGroup.get<TransformComponent, LightComponent>(entity);

            _sceneData.Lights.emplace_back(Light {
                .Position = transform.GetPosition(),
                .AmbientColor = light.AmbientColor,
                .DiffuseColor = light.DiffuseColor,
                .SpecularColor = light.SpecularColor,
            });
        }

        auto cameraGroup = _registry.group<CameraComponent>(entt::get<TransformComponent>);

        for (auto entity : cameraGroup) {
            auto [transform, camera] = cameraGroup.get<TransformComponent, CameraComponent>(entity);

            if (camera.IsActive()) {
                _sceneData.ProjectionMatrix = camera.GetProjectionMatrix();
                _sceneData.ViewMatrix = glm::inverse(transform.GetTransform());
                _sceneData.CameraPosition = transform.GetPosition();
                break;
            }
        }

        ServiceLocator::GetRenderer()->BeginScene();

        // Draw the objects
        auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto entity : group) {
            auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

            auto shader_ptr = mesh.GetShader().lock();
            bindSceneUniforms(shader_ptr);

            RenderCommand::DrawMesh(mesh, transform);
        }

        if (skybox) {
            glDepthFunc(GL_LEQUAL);
            auto& transform = skybox->GetComponent<TransformComponent>();
            auto& skyboxComp = skybox->GetComponent<SkyboxComponent>();

            auto shader_ptr = skyboxComp.GetShader().lock();
            bindSceneUniforms(shader_ptr);

            RenderCommand::DrawMesh(skyboxComp, transform);
            glDepthFunc(GL_LESS);
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

    void Scene::bindSceneUniforms(const std::shared_ptr<Shader>& shader_ptr) {

        assert(shader_ptr && "Cannot bind uniforms to null shader!");

        // add skybox texture to shader if there is one, otherwise remove it
        auto samplers = shader_ptr->GetTextureSamplers();
        auto skyboxSampler = std::find_if(samplers.begin(), samplers.end(), [](auto& sampler) {
           return sampler.samplerName == "skyboxTexture";
        });

        if (skybox) {
            auto &skyboxComponent = skybox->GetComponent<SkyboxComponent>();
            if (skyboxSampler == samplers.end() ||
                    skyboxSampler->texture->GetHandle() != skyboxComponent.GetShader().lock()->GetTextureSamplers()[0].texture->GetHandle()) {

                std::cout << "Attaching skybox to shader" << std::endl;
                samplers.emplace_back(
                    TextureSamplerBinding {
                        .samplerName = "skyboxTexture",
                        .index = TextureBindingIndex::Skybox,
                        .texture = skyboxComponent.GetShader().lock()->GetTextureSamplers()[0].texture
                    }
                );
                shader_ptr->SetTextureSamplers(std::move(samplers));
            }
        } else if (skyboxSampler != samplers.end()) {
            std::cout << "Removing skybox" << std::endl;
            samplers.erase(skyboxSampler);
        };

        if (shader_ptr && _lastShaderHandle != shader_ptr->GetHandle()) {
            shader_ptr->Bind();
            _lastShaderHandle = shader_ptr->GetHandle();
        }

        if (!_sceneData.Lights.empty()) {
            shader_ptr->Float3("light.position", _sceneData.Lights[0].Position);
            shader_ptr->Float3("light.ambientColor", _sceneData.Lights[0].AmbientColor);
            shader_ptr->Float3("light.diffuseColor", _sceneData.Lights[0].DiffuseColor);
            shader_ptr->Float3("light.specularColor", _sceneData.Lights[0].SpecularColor);
        }

        shader_ptr->Float3("cameraPosition", _sceneData.CameraPosition);

        shader_ptr->UniformMat4("u_projection", _sceneData.ProjectionMatrix);
        shader_ptr->UniformMat4("u_view", _sceneData.ViewMatrix);
    }

    void Scene::EnableSkybox() {
        skybox = CreateEntity();
        auto& transformBox = skybox->GetComponent<HE::TransformComponent>();
        transformBox.SetScale({2.f, 2.f, 2.f});
        skybox->AddComponent<HE::SkyboxComponent>();
    }

    void Scene::DisableSkybox() {
        RemoveEntity(skybox);
        skybox = nullptr;
    }

    void Scene::SetSkyboxTextureFace(TextureData &data, TextureTarget target) {
        if (!skybox) {
            EnableSkybox();
        }

        auto &skyboxComp = skybox->GetComponent<SkyboxComponent>();
        skyboxComp.SetTextureFace(data, target);
    }

    void Scene::SetSkyboxTextureFace(TextureData &&data, TextureTarget target) {
        SetSkyboxTextureFace(data, target);
    }
}