#pragma once
#include "pch.h"

namespace Crimson
{
    struct Color
    {
        inline static constexpr glm::vec4 WHITE = glm::vec4(1);
        inline static constexpr glm::vec4 BLACK = glm::vec4(0, 0, 0, 1);
        inline static constexpr glm::vec4 TRANSPARENT = glm::vec4(0, 0, 0, 0);
        inline static constexpr glm::vec4 BLUE = glm::vec4(0, 0, 1, 1);
        inline static constexpr glm::vec4 GREEN = glm::vec4(0, 1, 0, 1);
        inline static constexpr glm::vec4 RED = glm::vec4(1, 0, 0, 1);
        inline static constexpr glm::vec4 YELLOW = glm::vec4(1, 1, 0, 1);
        inline static constexpr glm::vec4 MAGENTA = glm::vec4(1, 0, 1, 1);
        inline static constexpr glm::vec4 CYAN = glm::vec4(0, 1, 1, 1);
    };
}
