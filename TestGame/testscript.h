#pragma once
#include "../crimson/crimson.h" // IWYU pragma: keep

namespace TestGame
{
    using namespace Crimson;

    class Testscript: public Script
    {
    public:
        using Script::Script;
        void init() override;
        void update() override;
        void render() override;
        ~Testscript() override = default;
    };
}