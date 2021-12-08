#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <hangout_engine/rendering/types.h>
#include <hangout_engine/rendering/shader.h>
#include <hangout_engine/rendering/texture.h>
#include "entity.h"

namespace HE {
    class Scene {
    public:
        Scene();

        ~Scene();

        Entity *CreateEntity();

        void SetClearColor(glm::vec3 clearColor) { _sceneData.ClearColor = clearColor; }

        void Update();
        void Render();
        void RemoveEntity(Entity *entity);

        void EnableSkybox();
        void DisableSkybox();
        void SetSkyboxTextureFace(TextureData& data, TextureTarget target);
        void SetSkyboxTextureFace(TextureData&& data, TextureTarget target);

    private:
        void bindSceneUniforms(const std::shared_ptr<Shader>& shader_ptr);


    private:
        uint32_t _lastShaderHandle = 0;
        SceneData _sceneData {};

        entt::registry _registry{};
        std::vector<std::unique_ptr<Entity>> _entities;
        Entity* skybox = nullptr;
    };
}
