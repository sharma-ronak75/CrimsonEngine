#include "../header/physics.h"
#include <format>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>

namespace Crimson::Physics
{
    bool is_colliding(PhysicsCollider& first, PhysicsCollider& second)
    {
        if(first.collider == second.collider) throw std::invalid_argument("both colliders are reference to the same object");
     
        if(first.collider->type() == "SphereCollider" && second.collider->type() == "SphereCollider")
        {
            return Crimson::Physics::Check::sphere_sphere(first, second);
        }
        if(first.collider->type() == "AABBCollider" && second.collider->type() == "AABBCollider")
        {
            return Crimson::Physics::Check::aabb_aabb(first, second);
        }
        else throw std::invalid_argument(std::format(
            "collision resolution not defined for first={} second={}",
                first.collider->type(),
                second.collider->type()
            ));
    }

    namespace Check
    {
        bool sphere_sphere(PhysicsCollider& first, PhysicsCollider& second)
        {
            auto collider_first = std::dynamic_pointer_cast<SphereCollider>(first.collider);
            auto collider_second = std::dynamic_pointer_cast<SphereCollider>(second.collider);
            const glm::vec3 delta = second.transform.position - first.transform.position;
            const float sqr_dist = glm::dot(delta, delta);

            return sqr_dist <= powf(collider_first->radius + collider_second->radius, 2.0F);
        }

        bool aabb_aabb(PhysicsCollider& first, PhysicsCollider& second)
        {
            auto collider_first = std::dynamic_pointer_cast<AABBCollider>(first.collider);
            auto collider_second = std::dynamic_pointer_cast<AABBCollider>(second.collider);

            return (first.transform.position.x > second.transform.position.x && first.transform.position.x < second.transform.position.x + collider_second->x) ||
                   (first.transform.position.y > second.transform.position.y && first.transform.position.y < second.transform.position.y + collider_second->y) ||
                   (first.transform.position.z > second.transform.position.z && first.transform.position.z < second.transform.position.z + collider_second->z) ||
                   (second.transform.position.x > first.transform.position.x && second.transform.position.x < first.transform.position.x + collider_first->x)  ||
                   (second.transform.position.y > first.transform.position.y && second.transform.position.y < first.transform.position.y + collider_first->y)  ||
                   (second.transform.position.z > first.transform.position.z && second.transform.position.z < first.transform.position.z + collider_first->z);
        }
    }
}