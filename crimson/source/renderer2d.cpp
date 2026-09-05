#include "../header/renderer2d.h"
#include "../header/window.h"

namespace Crimson::Renderer::DefaultShaders
{
    RawShader rectangle, circle;
}

namespace Crimson::Renderer{

Camera _global_camera;
Camera& _active_camera = _global_camera;

void _init()
{
    DefaultShaders::rectangle = RawShader::load("crimson/shaders/rect.glsl");
    DefaultShaders::circle = RawShader::load("crimson/shaders/circle.glsl");
}

void set_camera(Camera& camera)
{
    _active_camera = camera;
}

void clear(glm::vec4 color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::vec2 get_aspect_scale()
{
    if(Window::aspect_ratio < 1.0f) return glm::vec2(Window::aspect_ratio_inverse, 1.0f);
    return glm::vec2(1.0f, Window::aspect_ratio);
}

void draw_rectangle(glm::vec2 centre, glm::vec2 scale, glm::vec4 color, float rotation)
{
    DefaultShaders::rectangle.use();
    DefaultShaders::rectangle.set_uniform("uposition", centre);
    DefaultShaders::rectangle.set_uniform("uscale", scale);
    DefaultShaders::rectangle.set_uniform("ucolor", color);
    DefaultShaders::rectangle.set_uniform("urotation", rotation);
    DefaultShaders::rectangle.set_uniform("uaspect_scale", get_aspect_scale());
    DefaultShaders::rectangle.set_uniform("ucamera_position", _active_camera.position);
    DefaultShaders::rectangle.set_uniform("ucamera_zoom", _active_camera.zoom);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void draw_circle(glm::vec2 centre, float radius, glm::vec4 color)
{
    DefaultShaders::circle.use();
    DefaultShaders::circle.set_uniform("uposition", centre);
    DefaultShaders::circle.set_uniform("uradius", radius);
    DefaultShaders::circle.set_uniform("ucolor", color);
    DefaultShaders::circle.set_uniform("uaspect_scale", get_aspect_scale());
    DefaultShaders::circle.set_uniform("ucamera_position", _active_camera.position);
    DefaultShaders::circle.set_uniform("ucamera_zoom", _active_camera.zoom);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void draw_line(glm::vec2 start, glm::vec2 end, glm::vec4 color, float thickness)
{
    glm::vec2 centre = (start + end) * 0.5f;
    float angle = atan2f(end.y - start.y, end.x - start.x);
    draw_rectangle(centre, glm::vec2(glm::length(end - start), thickness), color, angle);
}

glm::vec2 screen_to_camera_space(glm::vec2 pos)
{
    pos /= glm::vec2(Window::get_size());
    pos -= 0.5f;
    pos *= glm::vec2(1, -1);
    pos *= 2;
    
    pos /= get_aspect_scale();
    pos *= 1000;
    return pos;
}

glm::vec2 screen_to_world_space(glm::vec2 pos)
{
    // what was i thinking? i dont know
    return screen_to_camera_space(pos) / _active_camera.zoom - _active_camera.position;
}


}; // namespace Crimson::Renderer
