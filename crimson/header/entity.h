#pragma once

#include "component.h"
#include <stdexcept>
#include <unordered_map>
namespace Crimson
{
    class Entity
    {
    private:
        std::unordered_map<std::string, Component*> components;
    public:

        Entity() = default;

        template<typename C> void add_component();
        template<typename C> void remove_component();
        template<typename C> C& get_component();
        template<typename C> bool has_component();

        const std::unordered_map<std::string, Component*>& get_component_list() const;
    };

    template<typename C> void Entity::add_component()
    {
        for(auto& [N, component]: components)
        {
            if(C().type() == N) throw std::invalid_argument("another component with the same type already exists");
        }

        components.emplace(C().type(), new C());
    }

    template<typename C> void Entity::remove_component()
    {
        for(auto& [N, component]: components)
        {
            if(C().type() != N) continue;
            components.erase(C().type());
            return;
        }

        throw std::runtime_error(std::format("cannot remove component {}, it doesn't exist", C().type()));
    }

    template<typename C> C& Entity::get_component()
    {
        for(auto& [N, component]: components)
        {
            if(C().type() != N) continue;
            return *(C*)component;
        }

        throw std::runtime_error(std::format("cannot find component {}, it doesn't exist", C().type()));
    }
    
    template<typename C> bool Entity::has_component()
    {
        for(auto& [N, component]: components)
        {
            if(C().type() != N) continue;
            return true;
        }

        return false;
    }

    inline const std::unordered_map<std::string, Component*>& Entity::get_component_list() const
    {
        return components;
    }
}