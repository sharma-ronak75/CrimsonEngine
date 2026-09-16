#pragma once
#include "component/transform.h"
#include <string>

namespace Crimson::Physics
{
    class Collider
    {
    public:
        virtual std::string type() const noexcept = 0;
    };

    class SphereCollider: Collider
    {
    public:
        float radius{1.0F};

        virtual std::string type() const noexcept override { return "SphereCollider"; }
    };

    class AABBCollider: Collider
    {
    public:
        float x{1.0F};
        float y{1.0F};
        float z{1.0F};

        virtual std::string type() const noexcept override { return "AABBCollider"; }
    };

    struct PhysicsCollider
    {
        Transform transform{};
        std::shared_ptr<Collider> collider;
    };
}