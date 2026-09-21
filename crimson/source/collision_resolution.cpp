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
        float pdiff1 = glm::dot(first.position - this->first.position, first.position - this->first.position);
        float pdiff2 = glm::dot(second.position - this->second.position, second.position - this->second.position);
        float rdiff1 = glm::dot(first.rotation - this->first.rotation, first.rotation - this->first.rotation);
        float rdiff2 = glm::dot(second.rotation - this->second.rotation, second.rotation - this->second.rotation);
        float sdiff1 = glm::dot(first.scale - this->first.scale, first.scale - this->first.scale);
        float sdiff2 = glm::dot(second.scale - this->second.scale, second.scale - this->second.scale);
        return pdiff1 < 1e-3 && pdiff2 < 1e-3 && rdiff1 < 1e-3 && rdiff2 < 1e23 && sdiff1 < 1e-3 && sdiff2 < 1e-3;
    }
}