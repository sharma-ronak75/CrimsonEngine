#pragma once
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/vector_float3.hpp>
#include "mesh.h"
#include "material.h"

namespace Crimson
{
    class Component
    {
    public:
        Component() = default;

        virtual std::string type() const noexcept { return "Base"; }
    };

    class Transform: public Component
    {
    public:
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale{};

        Transform() = default;
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
        virtual std::string type() const noexcept override { return "Transform"; }

        glm::mat3 get_rotation_matrix() const noexcept;
        glm::vec3 get_forward() const noexcept;
        glm::vec3 get_right() const noexcept;
        glm::vec3 get_up() const noexcept;
        glm::mat4 get_view_matrix(glm::vec3 world_up = glm::vec3(0, 1, 0)) const noexcept;
    };

    class Camera: public Component
    {
    public:
        float fov{70.F};
        float near_plane{0.1F};
        float far_plane{500.0F};
        glm::vec3 world_up{};

        Camera() = default;
        Camera(float fov, float near_plane, float far_plane, glm::vec3 world_up): fov(fov), near_plane(near_plane), far_plane(far_plane) {}
        virtual std::string type() const noexcept override { return "Camera"; }


        glm::mat4 get_projection_matrix() const noexcept;
    };

    class MeshRenderer: public Component
    {
    public:
        Mesh* mesh = nullptr;
        Material material{};
        GLuint vbo{};

        MeshRenderer();
        MeshRenderer(Mesh& mesh, Material material);
        ~MeshRenderer();

        void bind() const;

        virtual std::string type() const noexcept override { return "MeshRenderer"; }
    };
}