#include <hangout_engine/core/components/skybox_component.h>
#include "hangout_engine/utils/shapes.h"
#include "hangout_engine/service_locator.h"
#include <iostream>

namespace HE {
    constexpr auto vertexCode = R"(
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec2 aTexCoord;
        layout (location = 3) in vec3 aNormal;

        out vec3 TexCoords;

        uniform mat4 u_model;
        uniform mat4 u_projection;
        uniform mat4 u_view;

        void main()
        {
            TexCoords = aPos;
            vec4 pos = u_projection * mat4(mat3(u_view)) * u_model * vec4(aPos, 1.0);
            gl_Position = pos.xyww;
        }
    )";

    constexpr auto fragmentCode = R"(
        precision highp float;

        out vec4 FragColor;

        in vec3 TexCoords;

        uniform samplerCube skyboxTexture;

        void main()
        {
            FragColor = texture(skyboxTexture, TexCoords);
        }
    )";


    SkyboxComponent::SkyboxComponent() :
        MeshComponent(
            std::vector<Vertex>(cubeVertices.begin(), cubeVertices.end()),
            std::vector<uint32_t>(invertedCubeIndices.begin(), invertedCubeIndices.end())
        )
    {
        auto skyboxTexture = ServiceLocator::GetRenderer()->CreateTexture(TextureType::CUBEMAP);
        skyboxTexture->Bind();

        // Initialize the data
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_NEG_Z);
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_POS_X);
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_NEG_X);
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_POS_Y);
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_NEG_Y);
        skyboxTexture->UploadData(TextureData(100, 100, {1.f, 0.f, 1.f}), TextureTarget::CUBEMAP_POS_Z);

        auto shader = ServiceLocator::GetRenderer()->CreateShader();
        shader->Compile(vertexCode, fragmentCode);
        shader->SetTextureSamplers({
            {
                .samplerName = "skyboxTexture",
                .index = TextureBindingIndex::Skybox,
                .texture = skyboxTexture
            }
        });

        SetShader(std::move(shader));
    }

    void SkyboxComponent::SetTextureFace(TextureData &data, const TextureTarget target) {
        if (auto shader_ptr = GetShader().lock()) {
            auto skyboxTexture = std::find_if(shader_ptr->GetTextureSamplers().begin(), shader_ptr->GetTextureSamplers().end(), [](auto& sampler){
                return sampler.samplerName == "skyboxTexture";
            });

            skyboxTexture->texture->UploadData(data, target);

        }
    }

    void SkyboxComponent::SetTextureFace(TextureData &&data, const TextureTarget target) {
        SetTextureFace(data, target);
    }
}