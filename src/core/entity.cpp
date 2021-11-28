#include <hangout_engine/core/entity.h>
#include <iostream>
#include <hangout_engine/core/components/transform_component.h>

namespace HE {
    Entity::Entity(entt::registry &registry) : _registry(registry) {
        // Create entity in registry
        entt::entity entity_id = registry.create();
        id = (uint32_t) entity_id;

        AddComponent<TransformComponent>();
    }

/**
 * The entity destructor needs to remember to remove itself from the scene
 */
    Entity::~Entity() {
        std::cout << "DEBUG: Entity being destroyed!" << std::endl;

        // TODO: Do i need to explicitely call component destructors here?

        _registry.destroy((entt::entity) id);
    }

}

