#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>
#include <entt/entt.hpp>

/**
 * Entities are owned by the scene.
 *
 */
namespace HE {
    class Entity {
    public:
        explicit Entity(entt::registry &registry);

        ~Entity();

        template<typename T, typename... Args>
        T &AddComponent(Args &&... args) {
            if (_registry.all_of<T>((entt::entity) id)) {
                std::cout << "Entity " << id << " already has component." << std::endl;
                assert(false && "Entity already has component!");
            }
            return _registry.emplace<T>((entt::entity) id, std::forward<Args>(args)...);
        }

        template<typename T>
        void RemoveComponent() {
            _registry.remove<T>((entt::entity) id);
        }

        template<typename T>
        T &GetComponent() {
            return _registry.get<T>((entt::entity) id);
        }

        template<typename T, typename... Args>
        const T &UpdateComponent(Args &&... args) {
            return _registry.replace<T>((entt::entity) id, std::forward<Args>(args)...);
        }

        [[nodiscard]] inline uint32_t GetId() const { return id; }

    private:
        uint32_t id;
        entt::registry &_registry;
    };
}