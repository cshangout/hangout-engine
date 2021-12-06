#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <hangout_engine/rendering/types.h>
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


    private:
        SceneData _sceneData {};

        entt::registry _registry{};
        std::vector<std::unique_ptr<Entity>> _entities;
    };
}
