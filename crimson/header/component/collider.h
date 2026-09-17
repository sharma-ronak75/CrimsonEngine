#pragma once
#include "component.h"
#include "../physics.h"

namespace Crimson
{
    class Collider: public Component
    {
    public:
        std::shared_ptr<Physics::Collider> collider{};
        Collider() = default;
    };
}