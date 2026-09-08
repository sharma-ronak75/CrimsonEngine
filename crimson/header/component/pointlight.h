#pragma once
#include "component.h"

namespace Crimson
{
    class PointLight: public Component
    {
    public:
        glm::vec3 color{1.0F};
        float intensity{1.0F};
        
        PointLight() = default;
        PointLight(glm::vec3 color, glm::vec3 position, float intensity): color(color), intensity(intensity) {}

        virtual std::string type() const noexcept override { return "PointLight"; }
    };
}