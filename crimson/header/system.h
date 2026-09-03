#pragma once

#include "entity.h"

namespace Crimson
{
    class System
    {
    public:
        virtual void initialize() const = 0;
        virtual void tick_preframe(std::vector<Entity*>& entities) const = 0;
        virtual void tick_postframe(std::vector<Entity*>& entities) const = 0;
        virtual std::string type() const noexcept { return "Base"; }
    };

    class RenderSystem: public System
    {
    private:
        Entity* active_camera = nullptr;
    public:
        virtual void initialize() const override;
        void tick_preframe(std::vector<Entity*>& entities) const override;
        void tick_postframe(std::vector<Entity*>& entities) const override;
        void set_active_camera(Entity& entity);
        virtual std::string type() const noexcept override { return "RenderSystem"; }
    };
}