#include <hangout_engine/core/components/mesh_component.h>
#include <hangout_engine/service_locator.h>

namespace HE {

    MeshComponent::MeshComponent(std::vector<Vertex> &&vertices, std::vector<uint32_t> &&indices, const BufferLayout&& layout) {
        _vao = ServiceLocator::GetRenderer()->CreateVertexArray();
        _vao->Bind();

        std::shared_ptr<VertexBuffer> vertexBuffer = ServiceLocator::GetRenderer()->CreateVertexBuffer();
        vertexBuffer->Bind();
        vertexBuffer->UploadData(vertices);

        vertexBuffer->SetLayout(layout);

        auto indexBuffer = ServiceLocator::GetRenderer()->CreateIndexBuffer();
        indexBuffer->Bind();
        indexBuffer->UploadData(indices);

        _vao->AddVertexBuffer(vertexBuffer);
        _vao->AddIndexBuffer(indexBuffer);
    }

}