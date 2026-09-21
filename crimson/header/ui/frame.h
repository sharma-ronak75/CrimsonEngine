#pragma once

#include "style.h"
#include <functional>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <vector>
namespace Crimson::UI
{
    class Frame
    {
    public:
        std::vector<std::shared_ptr<Frame>> frames;
        glm::ivec2 scale{};
        Style style{};
        
        Frame() = default;

    };

    class Button: public Frame
    {
    public:
        using Frame::Frame;
        std::function<void(std::shared_ptr<Button>)>& on_click;
        Button(auto a = [](std::shared_ptr<Button>) -> void {}): on_click(a) {}
    };
}