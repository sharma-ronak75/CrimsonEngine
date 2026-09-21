#pragma once
#include "component.h"
#include "transform.h"
#include <cmath>

namespace Crimson
{
    const glm::vec3 RIGIDBODY_VELOCITY_UNDEFINED = glm::vec3(std::nan(""));

    class Rigidbody: public Component
    {
    private:
        glm::vec3 last_position{RIGIDBODY_VELOCITY_UNDEFINED};
    public:
        glm::vec3 acceleration{};
        float mass{1.0F};
        bool is_static{false};
        float ambient_friction_coefficient{1.0F};
        float sliding_friction_coefficient{1.0F};
        float current_friction_cofficient{1.0F};
        
        Rigidbody() = default;
        void tick(Transform& transform, float delta_time) noexcept;
        void set_position(Transform& transform, const glm::vec3& position) noexcept;
        void set_velocity(const Transform& transform, const glm::vec3& velocity, float delta_time) noexcept;

        virtual std::string type() const noexcept { return "Rigidbody"; }
    };
}