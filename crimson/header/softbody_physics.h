#pragma once

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <vector>
namespace Crimson::SoftbodyPhysics
{
    constexpr size_t UndefinedNode = -1zu;

    class Node
    {
    private:
        glm::vec3 last_position{std::nanf("")};
    public:
        glm::vec3 position{};
        glm::vec3 acceleration{};
        float mass{1.0F};

        void tick(float delta_time) noexcept;
    };

    class Joint
    {
    public:
        size_t first{UndefinedNode};
        size_t second{UndefinedNode};
        float rest_distance{};

        void tick(Node& first, Node& second) noexcept;
    };

    class SoftbodyMesh
    {
    public:
        std::vector<Node> nodes;
        std::vector<Joint> joints;
        SoftbodyMesh() = default;

        void tick_dynamics(float delta_time) noexcept;
        void tick_joints();
    };
}