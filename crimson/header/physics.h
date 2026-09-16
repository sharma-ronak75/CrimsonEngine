#pragma once
#include "collider.h"
#include <memory>

namespace Crimson::Physics
{
    bool is_colliding(PhysicsCollider& first, PhysicsCollider& second);

    namespace Check
    {
        bool sphere_sphere(PhysicsCollider& first, PhysicsCollider& second);
        bool aabb_aabb(PhysicsCollider& first, PhysicsCollider& second);
    }
}