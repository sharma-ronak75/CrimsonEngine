#include "../../header/component/behavior.h"

namespace Crimson
{
    void Behavior::tick_preframe()
    {
        for(auto& script: scripts) script->update();
    }

    void Behavior::tick_postframe()
    {
        for(auto& script: scripts) script->render();
    }
}