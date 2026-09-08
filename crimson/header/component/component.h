#pragma once
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../mesh.h"
#include <memory>
#include "../material.h"

namespace Crimson
{
    class Component
    {
    public:
        Component() = default;

        virtual std::string type() const noexcept { return "Base"; }
        virtual ~Component() = default;
    };
}
