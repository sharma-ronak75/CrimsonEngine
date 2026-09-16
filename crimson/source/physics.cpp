#include "../header/physics.h"
#include <format>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>

namespace Crimson::Physics
{
    bool is_colliding(PhysicsCollider& first, PhysicsCollider& second)
    {
        if(first.collider == second.collider) throw std::invalid_argument("both PhysicsCollider cannot reference the same Collider");
     
        if(first.collider->type() == "SphereCollider" && second.collider->type() == "SphereCollider")
        {
            return Crimson::Physics::Check::sphere_sphere(first, second);
        }
        if(first.collider->type() == "AABBCollider" && second.collider->type() == "AABBCollider")
        {
            return Crimson::Physics::Check::aabb_aabb(first, second);
        }
        if(first.collider->type() == "SphereCollider" && second.collider->type() == "AABBCollider")
        {
            return Crimson::Physics::Check::sphere_aabb(first, second);
        }
        if(first.collider->type() == "AABBCollider" && second.collider->type() == "SphereCollider")
        {
            return Crimson::Physics::Check::sphere_aabb(second, first);
        }
        else throw std::invalid_argument(std::format(
            "collision check not defined for first={} second={}",
                first.collider->type(),
                second.collider->type()
            ));
    }

    CollisionResolution resolve(PhysicsCollider& first, PhysicsCollider& second)
    {
        if(first.collider == second.collider) throw std::invalid_argument("both PhysicsCollider cannot reference the same Collider");
     
        if(first.collider->type() == "SphereCollider" && second.collider->type() == "SphereCollider")
        {
            return Crimson::Physics::Resolve::sphere_sphere(first, second);
        }
        if(first.collider->type() == "AABBCollider" && second.collider->type() == "AABBCollider")
        {
            return Crimson::Physics::Resolve::aabb_aabb(first, second);
        }
        if(first.collider->type() == "SphereCollider" && second.collider->type() == "AABBCollider")
        {
            return Crimson::Physics::Resolve::sphere_aabb(first, second);
        }
        if(first.collider->type() == "AABBCollider" && second.collider->type() == "SphereCollider")
        {
            return Crimson::Physics::Resolve::sphere_aabb(second, first);
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

            return sqr_dist <= std::pow(collider_first->radius + collider_second->radius, 2.0F);
        }

        bool aabb_aabb(PhysicsCollider& first, PhysicsCollider& second)
        {
            auto collider_first = std::dynamic_pointer_cast<AABBCollider>(first.collider);
            auto collider_second = std::dynamic_pointer_cast<AABBCollider>(second.collider);

            return first.transform.position.x < second.transform.position.x + collider_second->x &&
                   first.transform.position.x + collider_first->x > second.transform.position.x  &&
                   first.transform.position.y < second.transform.position.y + collider_second->y &&
                   first.transform.position.y + collider_first->y > second.transform.position.y  &&
                   first.transform.position.z < second.transform.position.z + collider_second->z &&
                   first.transform.position.z + collider_first->z > second.transform.position.z;
        }

        bool sphere_aabb(PhysicsCollider& sphere, PhysicsCollider& aabb)
        {
            auto sphere_collider = std::dynamic_pointer_cast<SphereCollider>(sphere.collider);
            auto aabb_collider = std::dynamic_pointer_cast<AABBCollider>(aabb.collider);

            const glm::vec3 aabb_min = aabb.transform.position - glm::vec3(aabb_collider->x, aabb_collider->y, aabb_collider->z) * 0.5F;
            const glm::vec3 aabb_max = aabb.transform.position + glm::vec3(aabb_collider->x, aabb_collider->y, aabb_collider->z) * 0.5F;
            const glm::vec3 closest = glm::clamp(sphere.transform.position, aabb_min, aabb_max);
            const glm::vec3 delta = sphere.transform.position - closest;
            const float sqr_dist = glm::dot(delta, delta);

            return sqr_dist <= sphere_collider->radius * sphere_collider->radius;
        }
    }

    namespace Resolve
    {
        CollisionResolution sphere_sphere(PhysicsCollider& first, PhysicsCollider& second)
        {
            auto collider_first = std::dynamic_pointer_cast<SphereCollider>(first.collider);
            auto collider_second = std::dynamic_pointer_cast<SphereCollider>(second.collider);
            const glm::vec3 delta = second.transform.position - first.transform.position;
            const float sqr_dist = glm::dot(delta, delta);

            if(sqr_dist >= std::pow(collider_first->radius + collider_second->radius, 2.0F))
            {
                return CollisionResolution{first.transform, second.transform};
            }
            
            const float dist = std::sqrt(sqr_dist);
            const float dist_to_move   = dist - (collider_first->radius + collider_second->radius);
            const glm::vec3 direction  = delta / dist;
            first.transform.position  += direction * dist_to_move * 0.5F;
            second.transform.position -= direction * dist_to_move * 0.5F;
            return {first.transform, second.transform};
        }

        CollisionResolution aabb_aabb(PhysicsCollider& first, PhysicsCollider& second)
        {
            auto collider_first = std::dynamic_pointer_cast<AABBCollider>(first.collider);
            auto collider_second = std::dynamic_pointer_cast<AABBCollider>(second.collider);

            const glm::vec3 half_first{collider_first->x * 0.5F, collider_first->y * 0.5F, collider_first->z * 0.5F};
            const glm::vec3 half_second{collider_second->x * 0.5F, collider_second->y * 0.5F,collider_second->z * 0.5F};

            const glm::vec3 delta = second.transform.position - first.transform.position;
            const glm::vec3 overlap = half_first + half_second - glm::abs(delta);

            if(overlap.x <= 0.0F || overlap.y <= 0.0F || overlap.z <= 0.0F) return {first.transform, second.transform};

            if(overlap.x <= overlap.y && overlap.x <= overlap.z)
            {
                const float direction = delta.x >= 0.0F ? -1.0F : 1.0F;
                first.transform.position.x += direction * overlap.x * 0.5F;
                second.transform.position.x -= direction * overlap.x * 0.5F;
            }
            else if (overlap.y <= overlap.x && overlap.y <= overlap.z)
            {
                const float direction = delta.y >= 0.0F ? -1.0F : 1.0F;
                first.transform.position.y += direction * overlap.y * 0.5F;
                second.transform.position.y -= direction * overlap.y * 0.5F;
            }
            else
            {
                const float direction = delta.z >= 0.0F ? -1.0F : 1.0F;
                first.transform.position.z += direction * overlap.z * 0.5F;
                second.transform.position.z -= direction * overlap.z * 0.5F;
            }

            return {first.transform, second.transform};
        }

        CollisionResolution sphere_aabb(PhysicsCollider& sphere, PhysicsCollider& aabb)
        {
            auto collider_sphere = std::dynamic_pointer_cast<SphereCollider>(sphere.collider);
            auto collider_aabb = std::dynamic_pointer_cast<AABBCollider>(aabb.collider);

            const glm::vec3 half_size{collider_aabb->x * 0.5F, collider_aabb->y * 0.5F, collider_aabb->z * 0.5F};
            const glm::vec3 box_min = aabb.transform.position - half_size;
            const glm::vec3 box_max = aabb.transform.position + half_size;
            const glm::vec3 closest = glm::clamp(sphere.transform.position, box_min, box_max );
            const glm::vec3 delta = sphere.transform.position - closest;

            const float sqr_dist = glm::dot(delta, delta);
            const float radius = collider_sphere->radius;
            if (sqr_dist >= radius * radius) return {sphere.transform, aabb.transform};
            
            if (sqr_dist > 0.0F)
            {
                const float distance = std::sqrt(sqr_dist);
                const glm::vec3 normal = delta / distance;
                const float penetration = radius - distance;
                
                sphere.transform.position += normal * penetration * 0.5F;
                aabb.transform.position -= normal * penetration * 0.5F;

                return {sphere.transform, aabb.transform};
            }
            
            const glm::vec3 local = sphere.transform.position - aabb.transform.position;
            const float dx = half_size.x - std::abs(local.x);
            const float dy = half_size.y - std::abs(local.y);
            const float dz = half_size.z - std::abs(local.z);

            glm::vec3 normal;
            float distance;

            if (dx <= dy && dx <= dz)
            {
                normal = {local.x >= 0.0F ? 1.0F : -1.0F, 0.0F, 0.0F};
                distance = dx;
            }
            else if (dy <= dx && dy <= dz)
            {
                normal = {0.0F, local.y >= 0.0F ? 1.0F : -1.0F, 0.0F};
                distance = dy;
            }
            else
            {
                normal = {0.0F, 0.0F, local.z >= 0.0F ? 1.0F : -1.0F};
                distance = dz;
            }

            const float penetration = radius + distance;
            sphere.transform.position += normal * penetration * 0.5F;
            aabb.transform.position -= normal * penetration * 0.5F;

            return {sphere.transform, aabb.transform};
        }
    }
}