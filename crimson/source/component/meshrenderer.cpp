#include "../../header/component/meshrenderer.h"

namespace Crimson
{
    void MeshRenderer::bind() const noexcept
    {
        if(mesh == nullptr) return;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            mesh->mesh_data.size() * sizeof(Vertex),
            mesh->mesh_data.data(),
            GL_STATIC_DRAW
        );
        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, position)
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, tint)
        );
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(
            2, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, normal)
        );
        glEnableVertexAttribArray(2);
    }

    MeshRenderer::MeshRenderer()
    {
        glGenBuffers(1, &vbo);
    }
    
    MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, Material material):
        mesh(mesh), material(std::move(material))
    {
        glGenBuffers(1, &vbo);
    }

    MeshRenderer::~MeshRenderer()
    {
        if(vbo != 0) glDeleteBuffers(1, &vbo);
    }
}