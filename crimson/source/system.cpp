#include "../header/system.h"
#include "../header/window.h"
#include <glm/gtx/string_cast.hpp>
#include <stdexcept>

namespace Crimson
{
    void RenderSystem::initialize() const {};
    void RenderSystem::tick_preframe(std::vector<Entity*>& entities) const {};

    void RenderSystem::tick_postframe(std::vector<Entity*>& entities) const
    {
        std::vector<Entity*> mesh_entities;
        Entity* camera_entity = nullptr;
        for(auto entity: entities)
        {
            if(entity == nullptr) throw std::invalid_argument("entity was fond to be nullptr");
            if(
                entity->has_component<Transform>() &&
                entity->has_component<MeshRenderer>()
            )   mesh_entities.emplace_back(entity);

            if(entity != active_camera) continue;
            if(!entity->has_component<Camera>()) throw std::runtime_error("active camera entity had its Camera component detached");
            camera_entity = entity;
        }

        if(camera_entity == nullptr) return;
        glm::mat4 PV = camera_entity->get_component<Camera>().get_projection_matrix() * camera_entity->get_component<Transform>().get_view_matrix();

        for(auto mesh_entity: mesh_entities)
        {
            if(mesh_entity == nullptr) throw std::logic_error("fatal: entity found to be nullptr");
            auto& mesh_renderer = mesh_entity->get_component<MeshRenderer>();
            const Material& material = mesh_renderer.material;
            const Mesh* mesh = mesh_renderer.mesh;

            if(mesh == nullptr) continue;

            mesh_renderer.bind();
            material.set_shader_attribute("umvp", PV);
            material.set_shader_attribute("ucampos", camera_entity->get_component<Transform>().position);
            material.set_shader_attribute("ucamforward", camera_entity->get_component<Transform>().get_forward());
            material.set_shader_attribute("ucamright", camera_entity->get_component<Transform>().get_right());
            material.set_shader_attribute("ucamup", camera_entity->get_component<Transform>().get_up());
            material.set_shader_attribute("utime", Crimson::Window::get_ticked_time());
            
            material.shader.use();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    void RenderSystem::set_active_camera(Entity& entity)
    {
        if(!entity.has_component<Camera>()) throw std::invalid_argument("Cannot set entity as active camera, it doesn't have the Camera component");

        active_camera = &entity;
    }
}