#pragma once

#include "renderer_api.h"
#include <memory>
#include <hangout_engine/service_locator.h>
#include "vertex_array.h"

namespace HE {
    class RenderCommand {
    public:
        static inline void SetClearColor(const glm::vec4 &color) {
            getAPI()->SetClearColor(color);
        }

        static inline void Clear() {
            getAPI()->Clear();
        }

        static inline void DrawArray(const std::shared_ptr<VertexArray>& vertexArray) {
            getAPI()->DrawArray(vertexArray);
        }

        static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
            getAPI()->DrawIndexed(vertexArray);
        }

        static inline void DrawMesh(const MeshComponent& mesh, const TransformComponent& transform) {
            getAPI()->DrawMesh(mesh, transform);
        }

    private:
        static RendererAPI* getAPI() {
            return ServiceLocator::GetRenderer()->GetRendererAPI();
        }
    };
}