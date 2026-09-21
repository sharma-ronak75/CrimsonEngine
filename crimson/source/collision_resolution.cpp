#include "../header/collision_resolution.h"


namespace Crimson::Physics
{
    void CollisionResolution::apply(Crimson::Transform& first, Crimson::Transform& second) const noexcept
    {
        first = this->first;
        second = this->second;
    }

    CollisionResolution CollisionResolution::swap() const noexcept
    {
        return CollisionResolution{second, first};
    }

    bool CollisionResolution::similar_to(Crimson::Transform& first, Crimson::Transform& second) const noexcept
    {
        float diff1 = glm::dot(first.position - this->first.position, first.position - this->first.position);
        float diff2 = glm::dot(second.position - this->second.position, second.position - this->second.position);
        return diff1 < 1e-3 && diff2 < 1e-3;
    }
}