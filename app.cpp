#include "app.h"
#include "crimson/header/settings.h"

void App::Initialize()
{
    Crimson::Window::enable_face_culling();
    Crimson::Settings::show_debug_info = true;

    world_handler.add_system<Crimson::RenderSystem>();

    camera_entity = world_handler.add_entity();
    camera_entity->add_component<Crimson::Transform>();
    camera_entity->add_component<Crimson::Camera>();
    camera_entity->get_component<Crimson::Transform>().position = glm::vec3(0, 0, 5);
    camera_entity->get_component<Crimson::Camera>().world_up = glm::vec3(0, 1, 0);

    world_handler.get_system<Crimson::RenderSystem>().set_active_camera(camera_entity);
    world_handler.initialize_systems();

    auto mesh1 = Crimson::Primitive::create_cube();
    auto mesh2 = Crimson::Primitive::create_sphere(10);
    Crimson::Material material;
    material.shader = Crimson::RawShader::load("crimson/shaders/base_lit.glsl");

    entity1 = world_handler.add_entity();
    entity1->add_component<Crimson::Transform>();
    entity1->add_component<Crimson::MeshRenderer>();
    entity1->get_component<Crimson::Transform>().position = glm::vec3(-1.5f, 0, 0);
    entity1->get_component<Crimson::MeshRenderer>().mesh = mesh1;
    entity1->get_component<Crimson::MeshRenderer>().material = material;

    entity2 = world_handler.add_entity();
    entity2->add_component<Crimson::Transform>();
    entity2->add_component<Crimson::MeshRenderer>();
    entity2->get_component<Crimson::Transform>().position = glm::vec3(1.5f, 0, 0);
    entity2->get_component<Crimson::MeshRenderer>().mesh = mesh2;
    entity2->get_component<Crimson::MeshRenderer>().material = material;
}

void App::Update()
{
    if(camera_entity != nullptr) control(*camera_entity);
    world_handler.tick_preframe();

    if(Crimson::Input::is_key_pressed(Crimson::Key::ENTER)) animation_pause = !animation_pause;
    if(!animation_pause)
    {
        entity1->get_component<Crimson::Transform>().position.x = sinf(Crimson::Window::get_ticked_time() * 2.5) * 2.5;
        entity1->get_component<Crimson::Transform>().rotation.x += 1.5;
        entity1->get_component<Crimson::Transform>().rotation.z += 3.5;

        entity2->get_component<Crimson::Transform>().position.y = sinf(Crimson::Window::get_ticked_time() * 0.75) * 8.5;
        entity2->get_component<Crimson::Transform>().position.x = sinf(Crimson::Window::get_ticked_time() * 5.5) * 2.5;
        entity2->get_component<Crimson::Transform>().position.z = cosf(Crimson::Window::get_ticked_time() * 5.5) * 2.5;
        entity2->get_component<Crimson::Transform>().rotation.y += 0.5;
        entity2->get_component<Crimson::Transform>().rotation.z += 1.5;
    }
}

void App::Render()
{
    Crimson::Renderer::clear(Crimson::Color::BLACK);
    world_handler.tick_postframe();
}

void App::Destruct() {}

void App::control(Crimson::Entity& camera_entity)
{
    if(Crimson::Input::is_key_pressed(Crimson::Key::ESCAPE)) Crimson::Window::mouse_captured = !Crimson::Window::mouse_captured;
    if(Crimson::Input::is_key_pressed(Crimson::Key::RIGHT_SHIFT)) Crimson::Settings::wireframe_rendering = !Crimson::Settings::wireframe_rendering;
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
