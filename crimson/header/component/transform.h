#pragma once
#include "component.h"

namespace Crimson
{
    class Transform: public Component
    {
    public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{1.0};
    
    Transform() = default;
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
    virtual std::string type() const noexcept override { return "Transform"; }
    
    glm::mat3 get_rotation_matrix() const noexcept;
    glm::vec3 get_forward() const noexcept;
    glm::vec3 get_right() const noexcept;
    glm::vec3 get_up() const noexcept;
    glm::mat4 get_view_matrix(glm::vec3 world_up = glm::vec3(0, 1, 0)) const noexcept;
};
}