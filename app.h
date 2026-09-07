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
    std::shared_ptr<Crimson::Entity> entity1{nullptr};
    std::shared_ptr<Crimson::Entity> entity2{nullptr};
    std::shared_ptr<Crimson::Entity> entity3{nullptr};
    std::shared_ptr<Crimson::Entity> entity4{nullptr};
    bool animation_pause = true;

    void Initialize();
    void Update();
    void Render();
    void Destruct();

    void control(Crimson::Entity& camera_entity);
};
