//
// Created by Paul Mauviel on 2021-11-08.
//
#include "open_gl_renderer.h"

#include <hangout_engine/service_locator.h>
#include <SDL_video.h>
#include <hangout_engine/rendering/render_command.h>
#include "open_gl_graphics.h"
#include "open_gl_buffer.h"
#include "open_gl_shader.h"
#include "open_gl_vertex_array.h"
#include "open_gl_texture.h"

namespace HE {
    void OpenGLRenderer::Init(RendererSettings settings) {
        if (ServiceLocator::GetWindow()) {
            ServiceLocator::GetWindow()->MakeContextCurrent();
        }

#ifdef GLAD
        gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif
        std::cout << "GL_VERSION=" << glGetString(GL_VERSION) << std::endl;
        std::cout << "GRAPHICS CARD=" << glGetString(GL_RENDERER) << std::endl;
        std::cout << "VENDOR=" << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL_SHADING_LANGUAGE_VERSION=" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        glEnable(GL_DEPTH_TEST);

        _rendererAPI = std::make_unique<OpenGLRendererAPI>();
    }

    void OpenGLRenderer::Shutdown() {

    }

    void OpenGLRenderer::BeginScene() {
    }

    void OpenGLRenderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->Bind();
        shader->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

    void OpenGLRenderer::EndScene() {
        if (ServiceLocator::GetWindow()) {
            ServiceLocator::GetWindow()->SwapBuffer();
        }
    }

    std::shared_ptr<VertexBuffer> OpenGLRenderer::CreateVertexBuffer() {
        return std::make_shared<OpenGLVertexBuffer>();
    }

    std::shared_ptr<IndexBuffer> OpenGLRenderer::CreateIndexBuffer() {
        return std::make_shared<OpenGLIndexBuffer>();
    }

    std::shared_ptr<Shader> OpenGLRenderer::CreateShader() {
        return std::make_shared<OpenGLShader>();
    }

    std::shared_ptr<VertexArray> OpenGLRenderer::CreateVertexArray() {
        return std::make_shared<OpenGLVertexArray>();
    }

    RendererAPI* OpenGLRenderer::GetRendererAPI() {
        return _rendererAPI.get();
    }

    std::shared_ptr<Texture> OpenGLRenderer::CreateTexture() {
        return std::make_shared<OpenGLTexture>();
    }

}