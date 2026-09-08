#pragma once
#include "component.h"

namespace Crimson
{
    class MeshRenderer: public Component
    {
    public:
        std::shared_ptr<Mesh> mesh = nullptr;
        Material material{};
        GLuint vbo{};

        MeshRenderer();
        MeshRenderer(std::shared_ptr<Mesh> mesh, Material material);
        ~MeshRenderer();

        void bind() const noexcept;

        virtual std::string type() const noexcept override { return "MeshRenderer"; }
    };
}