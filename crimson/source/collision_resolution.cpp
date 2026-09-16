#include "../header/collision_resolution.h"


namespace Crimson::Physics
{
    void CollisionResolution::apply(Crimson::Transform& first, Crimson::Transform& second) const noexcept
    {
        first = this->first;
        second = this->second;
    }
}