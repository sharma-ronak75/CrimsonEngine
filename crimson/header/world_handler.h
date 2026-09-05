#pragma once

#include "entity.h"
#include "system.h"
#include <stdexcept>
#include <memory>

namespace Crimson
{
    class WorldHandler
    {
    private:
        std::vector<std::shared_ptr<Entity>> world_entities;
        std::vector<std::shared_ptr<System>> systems;
    public:

        std::shared_ptr<Entity> add_entity();
        void remove_entity(const Entity& entity);
        template<class system> void add_system();
        // template<class system> void remove_system();
        template<class system> bool has_system();
        template<class system> system& get_system();
        void initialize_systems();
        void intialize_systems();
        void tick_preframe();
        void tick_postframe();
    };

    template<class system> void WorldHandler::add_system()
    {
        for(auto& sys: systems)
        {
            if(sys->type() == system().type()) throw std::invalid_argument("a same type of system already exists");
        }

        systems.emplace_back(std::make_shared<system>());
    }

    template<class system> bool WorldHandler::has_system()
    {
        for(auto& sys: systems)
        {
            if(sys->type() == system().type()) return true;
        }
        return false;
    }
    
    template<class system> system& WorldHandler::get_system()
    {
        for(auto& sys: systems)
        {
            if(sys->type() == system().type()) return static_cast<system&>(*sys);
        }

        throw std::invalid_argument(std::format("system of type {} was not found", system().type()));
    }
}
