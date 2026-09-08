#pragma once
#include "component.h"
#include "../script.h"

namespace Crimson
{
    class Behaviour : public Component
    {
    private:
        std::vector<std::unique_ptr<Script>> scripts;
    public:

        Behaviour() = default;
        
        template<typename T> T& add_script()
        {
            static_assert(std::is_base_of_v<Script, T>, "T must derive from Script");
            auto script = std::make_unique<T>();
            T& result = *script;

            scripts.push_back(std::move(script));
            return result;
        }
    };
}