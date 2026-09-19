#include "app.h"
#include "crimson/header/collider.h"
#include "crimson/header/component/collider.h"
#include "crimson/header/component/meshrenderer.h"
#include "crimson/header/component/rigidbody.h"
#include "crimson/header/component/transform.h"
#include "crimson/header/material.h"
#include "crimson/header/mesh.h"
#include "crimson/header/system.h"
#include "crimson/header/window.h"
#include <memory>

void App::Initialize()
{
    Crimson::Window::enable_face_culling();
    Crimson::Settings::show_debug_info = true;

    world_handler.add_system<Crimson::BehaviorSystem>();
    world_handler.add_system<Crimson::PhysicsSystem>();
    world_handler.add_system<Crimson::LightingSystem>();
    world_handler.add_system<Crimson::RenderSystem>();

    camera_entity = world_handler.add_entity();
    camera_entity->add_component<Crimson::Transform>();
    camera_entity->add_component<Crimson::Camera>();
    camera_entity->get_component<Crimson::Camera>().world_up = glm::vec3(0, 1, 0);

    world_handler.get_system<Crimson::RenderSystem>().set_active_camera(camera_entity);
    world_handler.initialize_systems();

    visual = world_handler.add_entity();
    visual->add_component<Crimson::Transform>();
    visual->add_component<Crimson::DirectionalLight>();
    visual->get_component<Crimson::Transform>().rotation.x = -35;
    visual->get_component<Crimson::Transform>().rotation.y = 55;

    visual->add_component<Crimson::Enviroment>();
    visual->get_component<Crimson::Enviroment>().material = Crimson::Primitive::create_enviroment_material();
    visual->get_component<Crimson::Enviroment>().sun_bleed = glm::vec3(1.2, 1, 1);

    plane = world_handler.add_entity();
    plane->add_component<Crimson::Transform>();
    plane->add_component<Crimson::MeshRenderer>();
    plane->add_component<Crimson::Collider>();
    plane->add_component<Crimson::Rigidbody>();

    plane->get_component<Crimson::Transform>().position.y = -10;
    plane->get_component<Crimson::Transform>().scale = glm::vec3(100, 1, 100);
    plane->get_component<Crimson::MeshRenderer>().mesh = Crimson::Primitive::create_cube();
    plane->get_component<Crimson::MeshRenderer>().material = Crimson::Primitive::create_lit_material();
    plane->get_component<Crimson::MeshRenderer>().material.set_shader_attribute("utint", glm::vec3(1.0, 0.8, 0.7));
    plane->get_component<Crimson::Collider>().collider = std::make_shared<Crimson::Physics::AABBCollider>();

    // create_ball();
}

void App::create_ball()
{
    auto mesh = Crimson::Primitive::create_sphere();
    Crimson::Material material = Crimson::Primitive::create_lit_material();

    std::shared_ptr<Crimson::Entity> entity;

    entity = world_handler.add_entity();
    entity->add_component<Crimson::Transform>();
    entity->add_component<Crimson::MeshRenderer>();
    entity->get_component<Crimson::Transform>().position =
        glm::vec3(-1.5f, 0, 0.7) +
        glm::vec3((rand() % 10) * 0.1F, (rand() % 10) * 0.1F, (rand() % 10) * 0.1F);
    entity->get_component<Crimson::MeshRenderer>().mesh = mesh;
    entity->get_component<Crimson::MeshRenderer>().material = material;

    entity->add_component<Crimson::Rigidbody>();
    entity->add_component<Crimson::Collider>();
    entity->get_component<Crimson::Collider>().collider = std::make_shared<Crimson::Physics::SphereCollider>();
}

void App::Update()
{
    if(camera_entity != nullptr) control(*camera_entity);
    world_handler.tick_preframe(deltaTime);

    for(auto& entity: world_handler.get_entity_list())
    {
        if(!entity->has_component<Crimson::Rigidbody>()) continue;
        if(!entity->has_component<Crimson::Transform>()) continue;
        if(!entity->has_component<Crimson::Collider>()) continue;
        if(entity == plane) continue;

        entity->get_component<Crimson::Rigidbody>().acceleration.y -= 10.0F;
    }

    // if(Crimson::Window::get_tick() % 120 == 0) create_ball();
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
