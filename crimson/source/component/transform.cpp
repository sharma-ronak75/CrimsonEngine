#include "../../header/component/transform.h"

namespace Crimson
{
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
}