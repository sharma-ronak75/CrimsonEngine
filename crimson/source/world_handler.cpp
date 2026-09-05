#include "../header/world_handler.h"
#include <stdexcept>

namespace Crimson
{
    std::shared_ptr<Entity> WorldHandler::add_entity()
    {
        auto entity = std::make_shared<Entity>();
        world_entities.emplace_back(entity);
        return entity;
    }

    void WorldHandler::remove_entity(const Entity& entity)
    {
        for(auto it = world_entities.begin(); it != world_entities.end(); ++it)
        {
            if(*it == nullptr) throw std::runtime_error("w_entity was found to be nullptr");
            if(it->get() != &entity) continue;

            world_entities.erase(it);
            return;
        }

        throw std::invalid_argument("cannot remove entity, entity not found");
    }

    void WorldHandler::initialize_systems()
    {
        for(auto& system: systems)
        {
            system->initialize();
        }
    }

    void WorldHandler::intialize_systems()
    {
        initialize_systems();
    }

    void WorldHandler::tick_preframe()
    {
        for(auto& system: systems)
        {
            system->tick_preframe(world_entities);
        }
    }
    
    void WorldHandler::tick_postframe()
    {
        for(auto& system: systems)
        {
            system->tick_postframe(world_entities);
        }
    }
}
