#include "../../header/component/camera.h"
#include "../../header/window.h"

namespace Crimson
{
    glm::mat4 Camera::get_projection_matrix() const noexcept
    {
        return glm::perspective(glm::radians(fov), Crimson::Window::aspect_ratio, near_plane, far_plane);
    }
}