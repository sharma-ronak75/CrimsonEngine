#include "app.h"

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
}

void App::Update()
{
    world_handler.tick_preframe();
    App::control_camera(*camera_entity);
}

void App::Render()
{
    Crimson::Renderer::clear();

    world_handler.tick_postframe();
}

void App::Destruct()
{
}

void App::control_camera(Crimson::Entity& camera_entity)
{
    if(Crimson::Input::is_key_pressed(Crimson::Key::ESCAPE)) Crimson::Window::mouse_captured = !Crimson::Window::mouse_captured;
    if(!Crimson::Window::mouse_captured) return;

    auto& transform = camera_entity.get_component<Crimson::Transform>();
    const float sensitivity = 0.05F;
    transform.rotation.y -= Crimson::Input::mouse_delta.x * sensitivity;
    transform.rotation.x -= Crimson::Input::mouse_delta.y * sensitivity;

    glm::vec3 movement{};
    if(Crimson::Input::is_key_down(Crimson::Key::W)) movement += transform.get_forward() * glm::vec3(1, 0, 1);
    if(Crimson::Input::is_key_down(Crimson::Key::S)) movement -= transform.get_forward() * glm::vec3(1, 0, 1);
    if(Crimson::Input::is_key_down(Crimson::Key::A)) movement -= transform.get_right() * glm::vec3(1, 0, 1);
    if(Crimson::Input::is_key_down(Crimson::Key::D)) movement += transform.get_right() * glm::vec3(1, 0, 1);
    if(Crimson::Input::is_key_down(Crimson::Key::SPACE)) movement.y ++;
    if(Crimson::Input::is_key_down(Crimson::Key::LEFT_SHIFT)) movement.y --;
    if(glm::length(movement) != 0) movement = glm::normalize(movement);

    const float speed = 0.25F;
    transform.position += movement * speed;
}