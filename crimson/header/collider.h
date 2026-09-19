#pragma once
#include "component/transform.h"
#include <limits>
#include <string>

namespace Crimson::Physics
{
    class Collider
    {
    public:
        virtual std::string type() const noexcept = 0;
    };

    class SphereCollider: public Collider
    {
    public:
        float radius{1.0F};
        
        SphereCollider() = default;
        SphereCollider(float radius): radius(radius) {}
        virtual std::string type() const noexcept override { return "SphereCollider"; }
    };
    
    class AABBCollider: public Collider
    {
    public:
        float x{1.0F};
        float y{1.0F};
        float z{1.0F};
        
        AABBCollider() = default;
        AABBCollider(float x, float y, float z): x(x), y(y), z(z) {}
        virtual std::string type() const noexcept override { return "AABBCollider"; }
    };

    struct PhysicsCollider
    {
        Transform transform{};
        std::shared_ptr<Collider> collider;
        float mass{1.0F};
    };

    class MassRatioOverride
    {
    public:
        float f1{std::nanf("")};
        float f2{std::nanf("")};

        inline MassRatioOverride swap() const noexcept { return MassRatioOverride{f2, f1}; }
    };
}