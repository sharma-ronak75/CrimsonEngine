#pragma once

#include "pch.h"
#include "rawshader.h"

namespace Crimson::Renderer::DefaultShaders
{
    extern RawShader rectangle, circle;
}

namespace Crimson::Renderer
{
    struct Camera
    {
        glm::vec2 position = {};
        float zoom = 1.0F;
    };

    extern Camera _global_camera;
    extern Camera& _active_camera;

    void _init();
    void set_camera(Camera& camera);
    void clear(glm::vec4 color = glm::vec4(0, 0, 0, 1));
    glm::vec2 get_aspect_scale();
    void draw_rectangle(glm::vec2 centre, glm::vec2 scale, glm::vec4 color = glm::vec4(1), float rotation = 0);
    void draw_circle(glm::vec2 centre, float radius, glm::vec4 color = glm::vec4(1));
    void draw_line(glm::vec2 start, glm::vec2 end, glm::vec4 color = glm::vec4(1), float thickness = 3);
    glm::vec2 screen_to_camera_space(glm::vec2 pos);
    glm::vec2 screen_to_world_space(glm::vec2 pos);
};