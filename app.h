#pragma once

#include "crimson/crimson.h"
#include "crimson/header/entity.h"
#include "crimson/header/world_handler.h"

struct App
{
    int tick = 0;           // Number of frames passed since creation of the window
    float deltaTime = 0;    // Time elapsed since last frame
    Crimson::WorldHandler world_handler;
    std::shared_ptr<Crimson::Entity> camera_entity;
    std::shared_ptr<Crimson::Entity> entity1;
    std::shared_ptr<Crimson::Entity> entity2;

    void Initialize();
    void Update();
    void Render();
    void Destruct();

    void control_camera(Crimson::Entity& camera_entity);
};
