#pragma once
#include "component.h"

namespace Crimson
{
    class Camera: public Component
    {
    public:
        float fov{70.F};
        float near_plane{0.1F};
        float far_plane{500.0F};
        glm::vec3 world_up{};

        Camera() = default;
        Camera(float fov, float near_plane, float far_plane, glm::vec3 world_up): fov(fov), near_plane(near_plane), far_plane(far_plane), world_up(world_up) {}
        virtual std::string type() const noexcept override { return "Camera"; }


        glm::mat4 get_projection_matrix() const noexcept;
    };
}