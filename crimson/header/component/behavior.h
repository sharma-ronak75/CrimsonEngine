#pragma once
#include "component.h"
#include "../script.h"

namespace Crimson
{
    class Behavior : public Component
    {
    private:
        std::vector<std::shared_ptr<Script>> scripts;
    public:
        Behavior() = default;
        
        template<typename T> T& add_script(std::shared_ptr<Entity>& entity)
        {
            static_assert(std::is_base_of_v<Script, T>, "T must derive from Script");
            auto script = std::make_shared<T>(entity);
            if(script == nullptr) throw std::bad_alloc();

            script->init();
            T& result = *script;
            scripts.push_back(script);

            return result;
        };

        void tick_preframe();
        void tick_postframe();
    };
}