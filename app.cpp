#include "app.h"
#include "crimson/header/component.h"
#include "crimson/header/material.h"
#include "crimson/header/mesh.h"
#include "crimson/header/system.h"
#include "crimson/header/window.h"
#include <glm/gtx/string_cast.hpp>

void App::Initialize()
{
    Crimson::Window::disable_face_culling();
    Crimson::Settings::show_debug_info = true;

    entity = &world_handler.add_entity();
    entity->add_component<Crimson::Transform>();
    entity->add_component<Crimson::MeshRenderer>();
    auto& mesh_renderer = entity->Crimson::Entity::get_component<Crimson::MeshRenderer>();
    mesh_renderer.mesh = Crimson::Primitive::create_plane();
    mesh_renderer.material = Crimson::Material(Crimson::RawShader::load("crimson/shaders/base_unlit.glsl"));

    world_handler.add_system<Crimson::RenderSystem>();
    world_handler.intialize_systems();

    camera_entity = &world_handler.add_entity();
    camera_entity->add_component<Crimson::Camera>();
    camera_entity->add_component<Crimson::Transform>();
    camera_entity->get_component<Crimson::Transform>().position.z = 5;

    world_handler.get_system<Crimson::RenderSystem>().set_active_camera(*camera_entity);

    // TODO: write macro to autogen structure and functionptr for binding the data of Mesh
    // TODO: write the base shaders
    // TODO: test the renderer
}

void App::Update()
{
    world_handler.tick_preframe();
}

void App::Render()
{
    Crimson::Renderer::clear();

    world_handler.tick_postframe();
}

void App::Destruct()
{
}
