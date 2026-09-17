#include "../../header/component/behavior.h"
#include <stdexcept>

namespace Crimson
{
    void Behavior::tick_preframe()
    {
        for(auto& script: scripts)
        {
            if(script == nullptr) throw std::invalid_argument("script was found to be nullptr");
            script->update();
        }
    }

    void Behavior::tick_postframe()
    {
        for(auto& script: scripts)
        {
            if(script == nullptr) throw std::invalid_argument("script was found to be nullptr");
            script->render();
        }
    }
}