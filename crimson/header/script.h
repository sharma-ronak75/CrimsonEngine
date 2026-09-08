#pragma once

#include "entity.h"

namespace Crimson
{
    class Script
    {
    protected:
        std::shared_ptr<Entity> entity{nullptr};
    };
}