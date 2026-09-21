#include "../header/softbody_physics.h"
#include <format>
#include <glm/ext/quaternion_geometric.hpp>
#include <stdexcept>

namespace Crimson::SoftbodyPhysics
{
    void Node::tick(float delta_time) noexcept
    {
        if(std::isnan(last_position.x)) last_position = position;
        const glm::vec3 velocity = position - last_position;
        last_position = position;
        position += velocity + acceleration * delta_time * delta_time;
    }

    void Joint::tick(Node& first, Node& second) noexcept
    {
        glm::vec3 delta = second.position - first.position;
        float magnitude_sqr = glm::dot(delta, delta);
        if(glm::abs(magnitude_sqr - rest_distance * rest_distance) < 1e3) return;

        float magnitude = glm::sqrt(magnitude);
        glm::vec3 direction = delta / magnitude;

        float first_mass_factor = second.mass / (first.mass + second.mass);
        float second_mass_factor = first.mass / (first.mass + second.mass);
        float move_distance = rest_distance - magnitude;
        
        first.position += direction * move_distance * first_mass_factor;
        second.position -= direction * move_distance * second_mass_factor;
    }

    void SoftbodyMesh::tick_dynamics(float delta_time) noexcept
    {
        for(auto& node: nodes) node.tick(delta_time);
    }

    void SoftbodyMesh::tick_joints()
    {
        for(auto& joint: joints)
        {
            if(joint.first >= nodes.size() || joint.second >= nodes.size())
            {
                throw std::runtime_error(
                    std::format("joint has unexpeced reference(s) first={} second={} while the size is {}", joint.first, joint.second, nodes.size())
                );
            }

            joint.tick(nodes[joint.first], nodes[joint.second]);
        }
    }
}