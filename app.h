#pragma once
#include "crimson/crimson.h"

struct App
{
    int tick = 0;           // Number of frames passed since creation of the window
    float deltaTime = 0;    // Time elapsed since last frame
    Crimson::WorldHandler world_handler;
    
    std::shared_ptr<Crimson::Entity> camera_entity;
    std::shared_ptr<Crimson::Entity> visual{nullptr};

    void Initialize();
    void Update();
    void Render();
    void Destruct();
    void create_ball();

    void control(Crimson::Entity& camera_entity);
};
