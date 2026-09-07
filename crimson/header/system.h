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
        virtual void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) = 0;
        virtual void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) = 0;
        virtual std::string type() const noexcept { return "Base"; }
    };

    class LightingSystem: public System
    {
    private:
        GLuint directional_light_SSBO{};
        GLuint point_light_SSBO{};
        std::vector<float> directional_light_buffer;
        std::vector<float> point_light_buffer;
    public:
        virtual void initialize() override;
        virtual void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) override;
        virtual void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) override;
        void bind(const Material& material) const;
        virtual std::string type() const noexcept override { return "LightingSystem"; }
    };

    class RenderSystem: public System
    {
    private:
        std::weak_ptr<Entity> active_camera;
        void render_mesh_entity(const std::shared_ptr<Entity>& mesh_entity, const std::shared_ptr<Entity>& camera_entity) const;
        void render_enviroment(const std::shared_ptr<Entity>& env_entity, const std::shared_ptr<Entity>& camera_entity) const;
        void set_camera_params(const Material& material, const std::shared_ptr<Entity>& camera_entity) const;
    public:

        virtual void initialize() override;
        void tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) override;
        void tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) override;
        void set_active_camera(const std::shared_ptr<Entity>& entity);
        

        virtual std::string type() const noexcept override { return "RenderSystem"; }
    };
}
