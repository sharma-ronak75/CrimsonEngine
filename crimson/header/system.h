#pragma once

#include "entity.h"
#include <memory>

namespace Crimson
{
    class System
    {
    public:
        virtual ~System() = default;
        virtual void initialize() = 0;
        virtual void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) const = 0;
        virtual void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) const = 0;
        virtual std::string type() const noexcept { return "Base"; }
    };

    class RenderSystem: public System
    {
    private:
        std::weak_ptr<Entity> active_camera;
        void render_mesh_entity(const std::shared_ptr<Entity>& mesh_entity, const std::shared_ptr<Entity>& camera_entity) const;
        void render_enviroment(const std::shared_ptr<Entity>& env_entity, const std::shared_ptr<Entity>& camera_entity) const;
        void set_camera_params(const Material& material, const std::shared_ptr<Entity>& camera_entity) const;
    public:
        Material enviroment_material{}; // temp public

        virtual void initialize() override;
        void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) const override;
        void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) const override;
        void set_active_camera(const std::shared_ptr<Entity>& entity);
        

        virtual std::string type() const noexcept override { return "RenderSystem"; }
    };
}
