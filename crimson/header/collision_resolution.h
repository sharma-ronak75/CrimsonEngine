#pragma once

#include "component/transform.h"
namespace Crimson::Physics
{
    class CollisionResolution
    {
    public:
        Crimson::Transform first;
        Crimson::Transform second;
        
        void apply(Crimson::Transform& first, Crimson::Transform& second) const noexcept;
        CollisionResolution swap() const noexcept;
        bool similar_to(Crimson::Transform& first, Crimson::Transform& second) const noexcept;
    };
}