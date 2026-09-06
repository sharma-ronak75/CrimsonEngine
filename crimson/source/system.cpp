#include "../header/system.h"
#include "../header/window.h"
#include <glm/gtx/string_cast.hpp>
#include <stdexcept>

namespace Crimson
{
    void RenderSystem::initialize()
    {
        enviroment_material = Material(RawShader::load("crimson/shaders/enviroment.glsl"));
    };

    void RenderSystem::tick_preframe(std::vector<std::shared_ptr<Entity>>& entities) const {};

    void RenderSystem::tick_postframe(std::vector<std::shared_ptr<Entity>>& entities) const
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

        if(env_entity != nullptr)
        {
            render_enviroment(env_entity, camera_entity);
        }

        for(auto& mesh_entity: mesh_entities)
        {
            render_mesh_entity(mesh_entity, camera_entity);
        }
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
        material.set_shader_attribute("utime", Crimson::Window::get_ticked_time());
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
        
        set_camera_params(enviroment_material, camera_entity);
        // TODO: set env props to shader
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
