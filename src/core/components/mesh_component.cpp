#include <hangout_engine/core/components/mesh_component.h>
#include <hangout_engine/service_locator.h>

namespace HE {

    MeshComponent::MeshComponent(std::vector<Vertex> &&vertices, std::vector<uint32_t> &&indices) {
        std::shared_ptr<VertexBuffer> vertexBuffer = ServiceLocator::GetRenderer()->CreateVertexBuffer();
        vertexBuffer->Bind();
        vertexBuffer->UploadData(vertices);

        HE::BufferLayout layout = {
                {HE::ShaderDataType::Float3, "aPos"},
                {HE::ShaderDataType::Float4, "aColor"},
                {HE::ShaderDataType::Float2, "aTexCoord"},
                {HE::ShaderDataType::Float3, "aNormal"},
        };

        vertexBuffer->SetLayout(layout);

        auto indexBuffer = ServiceLocator::GetRenderer()->CreateIndexBuffer();
        indexBuffer->Bind();
        indexBuffer->UploadData(indices);

        _vao = ServiceLocator::GetRenderer()->CreateVertexArray();
        _vao->AddVertexBuffer(vertexBuffer);
        _vao->AddIndexBuffer(indexBuffer);
    }

}