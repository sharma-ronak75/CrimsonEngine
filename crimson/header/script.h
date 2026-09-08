#pragma once

#include "entity.h"

namespace Crimson
{
    class Script
    {
    protected:
        std::shared_ptr<Entity> entity{nullptr};
    public:
        Script(std::shared_ptr<Entity>& entity): entity(entity) {}
        
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        virtual ~Script() = default;
    };
}