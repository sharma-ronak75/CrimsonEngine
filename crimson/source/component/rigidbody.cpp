#include "../../header/component/rigidbody.h"

namespace Crimson
{
    void Rigidbody::tick(Transform& transform, float delta_time) noexcept
    {
        if(std::isnan(last_position.x)) last_position = transform.position;

        const glm::vec3 velocity = transform.position - last_position;
        last_position = transform.position;
        transform.position = velocity + acceleration * delta_time * delta_time;
        acceleration = {};
    }


    void Rigidbody::set_position(Transform& transform, const glm::vec3& position) noexcept
    {
        transform.position = position;
        last_position = position;
    }

    void Rigidbody::set_velocity(const Transform& transform, const glm::vec3& velocity, float delta_time) noexcept
    {
        last_position = (transform.position - velocity) * delta_time;
    }
}