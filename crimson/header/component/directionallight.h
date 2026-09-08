#pragma once
#include "component.h"

namespace Crimson
{
    class DirectionalLight: public Component
    {
    public:
        glm::vec3 color{1.0F};
        float intensity{1.0F};
        bool is_sun{true};
        
        DirectionalLight() = default;
        DirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity): color(color), intensity(intensity) {}

        virtual std::string type() const noexcept override { return "DirectionalLight"; }
    };
}