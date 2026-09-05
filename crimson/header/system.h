#pragma once

#include "entity.h"
#include <memory>

namespace Crimson
{
    class System
    {
    public:
        virtual ~System() = default;
        virtual void initialize() const = 0;
        virtual void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) const = 0;
        virtual void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) const = 0;
        virtual std::string type() const noexcept { return "Base"; }
    };

    class RenderSystem: public System
    {
    private:
        std::weak_ptr<Entity> active_camera;
    public:
        virtual void initialize() const override;
        void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) const override;
        void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) const override;
        void set_active_camera(const std::shared_ptr<Entity>& entity);
        virtual std::string type() const noexcept override { return "RenderSystem"; }
    };
}
