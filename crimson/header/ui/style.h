#pragma once

#include <glm/ext/vector_float4.hpp>
namespace Crimson::UI
{
    class Style
    {
    public:
        glm::vec4 fill_color{1.0F};
        glm::vec4 border_color{0, 0, 0, 1.0F};
        float border_width{0.0F};
    };
}