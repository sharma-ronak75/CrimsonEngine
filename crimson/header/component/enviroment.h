#pragma once
#include "component.h"

namespace Crimson
{
    class Enviroment: public Component
    {
    public:
        glm::vec3 sun_color{0.8, 0.7, 0.1};
        glm::vec3 sky_color{0.4, 0.6, 0.95};
        glm::vec3 horizon_color{0.8};
        glm::vec3 zenith_color{0.3};
        float horizon_fade{2.5F};
        float sun_size{2.0F};
        float sun_strength{2.0F};
        glm::vec3 sun_bleed{1.0F};
        bool draw_sun{true};
        
        Material material;

        Enviroment() = default;
        Enviroment(const Material& material, glm::vec3 sun_color, glm::vec3 horizon_color, glm::vec3 zenith_color, float horizon_fade):
            sun_color(sun_color), horizon_color(horizon_color), zenith_color(zenith_color), horizon_fade(horizon_fade), material(material) {}

        virtual std::string type() const noexcept override { return "Enviroment"; }
    };
}