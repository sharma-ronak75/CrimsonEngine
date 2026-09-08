#include "../header/system.h"
#include "../header/window.h"
#include <glm/gtx/string_cast.hpp>
#include <stdexcept>
#include "../header/component/transform.h"
#include "../header/component/meshrenderer.h"
#include "../header/component/camera.h"
#include "../header/component/enviroment.h"
#include "../header/component/pointlight.h"
#include "../header/component/directionallight.h"
#include "../header/component/behavior.h"

namespace Crimson
{
    void LightingSystem::initialize()
    {
        if(directional_light_SSBO == 0) glGenBuffers(1, &directional_light_SSBO);
        if(point_light_SSBO == 0) glGenBuffers(1, &point_light_SSBO);
    }
    
    void LightingSystem::tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) {}
    void LightingSystem::tick_postframe(std::vector<std::shared_ptr<Entity>>& entities)
    {
        directional_light_buffer.clear();
        point_light_buffer.clear();
        for(auto& entity: entities)
        {
            if(
                entity->has_component<DirectionalLight>() &&
                entity->has_component<Transform>()
            )
            {
                directional_light_buffer.emplace_back(entity->get_component<Transform>().get_forward().x);
                directional_light_buffer.emplace_back(entity->get_component<Transform>().get_forward().y);
                directional_light_buffer.emplace_back(entity->get_component<Transform>().get_forward().z);
                directional_light_buffer.emplace_back(entity->get_component<DirectionalLight>().color.x);
                directional_light_buffer.emplace_back(entity->get_component<DirectionalLight>().color.y);
                directional_light_buffer.emplace_back(entity->get_component<DirectionalLight>().color.z);
                directional_light_buffer.emplace_back(entity->get_component<DirectionalLight>().intensity);
            }
            if(
                entity->has_component<PointLight>() &&
                entity->has_component<Transform>()
            )
            {
                point_light_buffer.emplace_back(entity->get_component<Transform>().position.x);
                point_light_buffer.emplace_back(entity->get_component<Transform>().position.y);
                point_light_buffer.emplace_back(entity->get_component<Transform>().position.z);
                point_light_buffer.emplace_back(entity->get_component<PointLight>().color.x);
                point_light_buffer.emplace_back(entity->get_component<PointLight>().color.y);
                point_light_buffer.emplace_back(entity->get_component<PointLight>().color.z);
                point_light_buffer.emplace_back(entity->get_component<PointLight>().intensity);
            }
        }

        for(auto& entity: entities)
        {
            if(
                entity->has_component<MeshRenderer>() &&
                entity->has_component<Transform>()
            )
            {
                auto& mesh_renderer = entity->get_component<MeshRenderer>();
                bind(mesh_renderer.material);
            }
            if(entity->has_component<Enviroment>())
            {
                auto& enviroment = entity->get_component<Enviroment>();
                bind(enviroment.material);
            }
        }
    }

    void LightingSystem::bind(const Material& material) const
    {
        material.shader.use();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, directional_light_SSBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * directional_light_buffer.size(), directional_light_buffer.data(), GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, directional_light_SSBO);
        material.set_shader_attribute<int>("udlbufsize", directional_light_buffer.size());

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, point_light_SSBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * point_light_buffer.size(), point_light_buffer.data(), GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, point_light_SSBO);
        material.set_shader_attribute<int>("uplbufsize", point_light_buffer.size());

        Crimson::RawShader::use_none();
    }

    void BehaviorSystem::initialize() {}
    void BehaviorSystem::tick_preframe(std::vector<std::shared_ptr<Entity>>& entities)
    {
        for(auto& entity: entities)
        { 
            if(entity->has_component<Crimson::Behavior>()) entity->get_component<Crimson::Behavior>().tick_preframe();
        }
    }

    void BehaviorSystem::tick_postframe(std::vector<std::shared_ptr<Entity>>& entities)
    {
        for(auto& entity: entities)
        { 
            if(entity->has_component<Crimson::Behavior>()) entity->get_component<Crimson::Behavior>().tick_postframe();
        }
    }


    void RenderSystem::initialize() {}
    void RenderSystem::tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) {};

    void RenderSystem::tick_postframe(std::vector<std::shared_ptr<Entity>>& entities)
    {
        std::vector<std::shared_ptr<Entity>> mesh_entities;
        std::shared_ptr<Entity> env_entity = nullptr;
        auto camera_entity = active_camera.lock();

        for(auto& entity: entities)
        {
            if(entity == nullptr) throw std::invalid_argument("entity was found to be nullptr");
            if(
                entity->has_component<Transform>() &&
                entity->has_component<MeshRenderer>()
            )   mesh_entities.emplace_back(entity);
            if(entity->has_component<Enviroment>()) env_entity = entity;

            if(entity != camera_entity) continue;
            if(!entity->has_component<Camera>()) throw std::runtime_error("active camera entity had its Camera component detached");
        }

        if(camera_entity == nullptr) return;
        if(env_entity != nullptr) render_enviroment(env_entity, camera_entity);
        for(auto& mesh_entity: mesh_entities) render_mesh_entity(mesh_entity, camera_entity);
    }

    void RenderSystem::set_camera_params(const Material& material, const std::shared_ptr<Entity>& camera_entity) const
    {
        if(camera_entity == nullptr) throw std::invalid_argument("camera_entity found to be nullptr");
        
        glm::mat4 PV = camera_entity->get_component<Camera>().get_projection_matrix() * camera_entity->get_component<Transform>().get_view_matrix();
        material.set_shader_attribute("umvp", PV);
        material.set_shader_attribute("ucampos", camera_entity->get_component<Transform>().position);
        material.set_shader_attribute("ucamforward", camera_entity->get_component<Transform>().get_forward());
        material.set_shader_attribute("ucamright", camera_entity->get_component<Transform>().get_right());
        material.set_shader_attribute("ucamup", camera_entity->get_component<Transform>().get_up());
        material.set_shader_attribute("ucamrot", camera_entity->get_component<Transform>().rotation);
        material.set_shader_attribute("utime", Crimson::Window::get_ticked_time()); // why
    }

    void RenderSystem::render_mesh_entity(const std::shared_ptr<Entity>& mesh_entity, const std::shared_ptr<Entity>& camera_entity) const
    {
        if(mesh_entity == nullptr) throw std::logic_error("fatal: entity found to be nullptr");
        auto& mesh_renderer = mesh_entity->get_component<MeshRenderer>();
        auto& material = mesh_renderer.material;
        auto mesh = mesh_renderer.mesh;
        auto& transform = mesh_entity->get_component<Transform>();

        if(mesh == nullptr) return;

        mesh_renderer.bind();
        set_camera_params(material, camera_entity);
        material.set_shader_attribute("umeshpos", transform.position);
        material.set_shader_attribute("umeshrot", transform.rotation);
        material.set_shader_attribute("umeshscale", transform.scale);
        material.shader.use();
        glDrawArrays(GL_TRIANGLES, 0, mesh->get_vertex_count());
    }

    void RenderSystem::render_enviroment(const std::shared_ptr<Entity>& env_entity, const std::shared_ptr<Entity>& camera_entity) const
    {
        if(env_entity == nullptr) throw std::invalid_argument("env_entity found to be nullptr");
        if(camera_entity == nullptr) throw std::invalid_argument("camera_entity found to be nullptr");

        const auto& enviroment = env_entity->get_component<Enviroment>();
        const auto& enviroment_material = enviroment.material;

        set_camera_params(enviroment_material, camera_entity);
        enviroment_material.set_shader_attribute("usun_color", enviroment.sun_color);
        enviroment_material.set_shader_attribute("uhorizon_color", enviroment.horizon_color);
        enviroment_material.set_shader_attribute("uzenith_color", enviroment.zenith_color);
        enviroment_material.set_shader_attribute("usky_color", enviroment.sky_color);
        enviroment_material.set_shader_attribute("usun_size", enviroment.sun_size);
        enviroment_material.set_shader_attribute("usun_strength", enviroment.sun_strength);
        enviroment_material.set_shader_attribute("usun_bleed", enviroment.sun_bleed);
        enviroment_material.set_shader_attribute("uhorizon_fade", enviroment.horizon_fade);
        enviroment_material.set_shader_attribute("udraw_sun", enviroment.draw_sun);
        
        enviroment_material.shader.use();
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glEnable(GL_DEPTH_TEST);
    }

    void RenderSystem::set_active_camera(const std::shared_ptr<Entity>& entity)
    {
        if(entity == nullptr || !entity->has_component<Camera>()) throw std::invalid_argument("Cannot set entity as active camera, it doesn't have the Camera component");

        active_camera = entity;
    }
}
