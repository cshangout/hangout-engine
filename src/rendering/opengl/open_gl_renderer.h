#pragma once
#include <hangout_engine/rendering/renderer.h>
#include <glm/vec4.hpp>
#include "open_gl_renderer_api.h"

namespace HE {
    class OpenGLRenderer : public Renderer {
    public:
        void Init(RendererSettings settings) override;
        void Shutdown() override;

        void BeginScene() override;
        void Submit(const std::shared_ptr<Shader>&, const std::shared_ptr<VertexArray>&) override;
        void EndScene() override;

        std::shared_ptr<VertexBuffer> CreateVertexBuffer() override;
        std::shared_ptr<IndexBuffer> CreateIndexBuffer() override;

        std::shared_ptr<Shader> CreateShader() override;
        std::shared_ptr<VertexArray> CreateVertexArray() override;

        std::shared_ptr<Texture> CreateTexture() override;

        RendererAPI* GetRendererAPI() override;

    private:

        std::unique_ptr<OpenGLRendererAPI> _rendererAPI = nullptr;
    };
}
