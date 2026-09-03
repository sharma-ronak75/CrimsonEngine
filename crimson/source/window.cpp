#include "../header/window.h"

namespace Crimson::Window{

std::string title = std::string("Crimson window");
float aspect_ratio = 1;
float aspect_ratio_inverse = 1;
int sample_rate = 1;
bool mouse_captured = false;
int __tick = 0;

void resize(int width, int height)
{
    glfwSetWindowSize(Input::window, width, height);
}

void set_size(int width, int height)
{
    glfwSetWindowSize(Input::window, width, height);
}

glm::ivec2 get_size()
{
    glm::ivec2 size;
    glfwGetWindowSize(Input::window, &size.x, &size.y);

    return size;
}

void set_resize_limit(glm::ivec2 min, glm::ivec2 max)
{
    glfwSetWindowSizeLimits(Input::window, min.x, min.y, max.x, max.y);
}

void set_opacity(float opacity)
{
    glfwSetWindowOpacity(Input::window, opacity);
}

float get_opacity()
{
    return glfwGetWindowOpacity(Input::window);
}

void set_position(int x, int y)
{
    glfwSetWindowPos(Input::window, x, y);
}

glm::ivec2 get_position()
{
    glm::ivec2 position;
    glfwGetWindowPos(Input::window, &position.x, &position.y);

    return position;
}

void fullscreen()
{
    std::cout<<"\033[1;31mFullscreen not supported yet, sorry!\n";
}

void maximize()
{
    glfwMaximizeWindow(Input::window);
}

void set_antialiasing_samplerate(int rate)
{
    glfwWindowHint(GLFW_SAMPLES, rate);
}

void enable_face_culling()
{
    glEnable(GL_CULL_FACE);
}

void disable_face_culling()
{
    glDisable(GL_CULL_FACE);
}

int get_tick()
{
    return __tick;
}

float get_ticked_time()
{
    return (float)__tick / 60.0f;
}
} // namespace Crimson::Window