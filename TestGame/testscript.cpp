#include "testscript.h"

namespace TestGame
{
    void Testscript::init() 
    {
    }

    void Testscript::update() 
    {
        entity->get_component<Transform>().position.x+=0.5;
    }

    void Testscript::render() {}
}