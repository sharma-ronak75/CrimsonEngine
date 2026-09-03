#include "../header/component.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/trigonometric.hpp>
#include "../header/window.h"

namespace Crimson
{
    // Transform
    glm::mat3 Transform::get_rotation_matrix() const noexcept
    {
        glm::vec3 r = glm::radians(rotation);

        return glm::mat3(
            glm::rotate(glm::mat4(1.0f), r.z, glm::vec3(0, 0, 1)) *
            glm::rotate(glm::mat4(1.0f), r.y, glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.0f), r.x, glm::vec3(1, 0, 0))
        );
    }

    glm::vec3 Transform::get_forward() const noexcept
    {
        return get_rotation_matrix() * glm::vec3(0, 0, -1);
    }

    glm::vec3 Transform::get_right() const noexcept
    {
        return get_rotation_matrix() * glm::vec3(1, 0, 0);
    }

    glm::vec3 Transform::get_up() const noexcept
    {
        return get_rotation_matrix() * glm::vec3(0, 1, 0);
    }

    glm::mat4 Transform::get_view_matrix(glm::vec3 world_up) const noexcept
    {
        return glm::lookAt(position, position + get_forward(), world_up);
    }

    // Camera

    glm::mat4 Camera::get_projection_matrix() const noexcept
    {
        return glm::perspective(glm::radians(fov), Crimson::Window::aspect_ratio, near_plane, far_plane);
    }

    // MeshRenderer

    void MeshRenderer::bind() const
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
    }

    MeshRenderer::MeshRenderer()
    {
        glGenBuffers(1, &vbo);
    }
    
    MeshRenderer::MeshRenderer(Mesh& mesh, Material material):
        mesh(&mesh), material(material)
    {
        glGenBuffers(1, &vbo);
    }

    MeshRenderer::~MeshRenderer()
    {
        if(vbo != 0) glDeleteBuffers(1, &vbo);
    }
}