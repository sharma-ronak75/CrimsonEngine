#include "../header/world_handler.h"
#include <stdexcept>

namespace Crimson
{
    Entity& WorldHandler::add_entity()
    {
        Entity* entity = new Entity();  
        if(entity == nullptr) throw std::runtime_error("memory allocation failed");
        
        world_entities.emplace_back(entity);
        return *entity;
    }

    void WorldHandler::remove_entity(const Entity& entity)
    {
        for(auto w_entity: world_entities)
        {
            if(w_entity == nullptr) throw std::runtime_error("w_entity was found to be nullptr");
            if(w_entity != &entity) continue;

            free(w_entity);
            return;
        }

        throw std::invalid_argument("cannot remove entity, entity not found");
    }

    void WorldHandler::intialize_systems()
    {
        for(auto system: systems)
        {
            system->initialize();
        }
    }

    void WorldHandler::tick_preframe()
    {
        for(auto system: systems)
        {
            system->tick_preframe(world_entities);
        }
    }
    
    void WorldHandler::tick_postframe()
    {
        for(auto system: systems)
        {
            system->tick_postframe(world_entities);
        }
    }
}