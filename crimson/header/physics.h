#pragma once
#include "collider.h"
#include "collision_resolution.h"
#include <memory>

namespace Crimson::Physics
{
    bool is_colliding(PhysicsCollider& first, PhysicsCollider& second);
    CollisionResolution resolve(PhysicsCollider& first, PhysicsCollider& second, MassRatioOverride mro = {});

    namespace Check
    {
        bool sphere_sphere(PhysicsCollider& first, PhysicsCollider& second);
        bool aabb_aabb(PhysicsCollider& first, PhysicsCollider& second);
        bool sphere_aabb(PhysicsCollider& sphere, PhysicsCollider& aabb);
    }

    namespace Resolve
    {
        CollisionResolution sphere_sphere(PhysicsCollider& first, PhysicsCollider& second, MassRatioOverride mro = {});
        CollisionResolution aabb_aabb(PhysicsCollider& first, PhysicsCollider& second, MassRatioOverride mro = {});
        CollisionResolution sphere_aabb(PhysicsCollider& sphere, PhysicsCollider& aabb, MassRatioOverride mro = {});
    }
}