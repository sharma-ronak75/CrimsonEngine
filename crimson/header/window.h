#pragma once

#include "pch.h"
#include "input.h"


namespace Crimson::Window
{
    extern std::string title;
    extern float aspect_ratio;
    extern float aspect_ratio_inverse;
    extern int sample_rate;
    extern bool mouse_captured;
    extern int __tick;

    void resize(int width, int height);
    void set_size(int width, int height);
    glm::ivec2 get_size();
    void set_resize_limit(glm::ivec2 min, glm::ivec2 max);
    void set_opacity(float opacity);
    float get_opacity();
    void set_position(int x, int y);
    glm::ivec2 get_position();
    void fullscreen();
    void maximize();
    void set_antialiasing_samplerate(int rate);
    void enable_face_culling();
    void disable_face_culling();
    int get_tick();
    float get_ticked_time();
};
