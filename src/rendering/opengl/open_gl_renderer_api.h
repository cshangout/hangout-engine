#pragma once
#include <hangout_engine/rendering/renderer_api.h>

namespace HE {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        void SetClearColor(const glm::vec4 &color) override;
        void Clear() override;

        void DrawArray(const std::shared_ptr<VertexArray> &ptr) override;
        void DrawIndexed(const std::shared_ptr<VertexArray>&) override;

    };
}

