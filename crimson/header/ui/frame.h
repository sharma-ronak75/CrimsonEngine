#pragma once

#include "style.h"
#include <functional>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <vector>
namespace Crimson::UI
{
    struct FrameBounds
    {
        glm::ivec2 position;
        glm::ivec2 scale;
    };

    class Frame
    {
    private:
        std::vector<std::function<void(std::shared_ptr<Frame>)>> events;
    public:
        std::vector<std::shared_ptr<Frame>> frames;
        glm::ivec2 scale{};
        Style style{};
        
        Frame() = default;
        void add_eventlistener(std::function<void(std::shared_ptr<Frame>)>);
        void remove_eventlistener(std::function<void(std::shared_ptr<Frame>)>);
        void tick_events();

        bool is_focused() const noexcept;
        bool is_mousepressed() const noexcept;
        bool is_mousedown() const noexcept;
        bool is_mouseup() const noexcept;
        bool is_keydown() const noexcept;
        bool is_keyup() const noexcept;
        bool is_keypressed() const noexcept;
        bool is_mouseenter() const noexcept;
        bool is_mouseexit() const noexcept;

        FrameBounds get_bounds() const noexcept;
    };

    class Button: public Frame
    {
    public:
        using Frame::Frame;
        std::function<void(std::shared_ptr<Button>)>& on_click;
        Button(auto a = [](std::shared_ptr<Button>) -> void {}): on_click(a) {}
    };

    class Dropdown: public Frame
    {
    public:
        using Frame::Frame;
        std::vector<std::shared_ptr<Frame>> options;
        int selected = -1;

        std::shared_ptr<Frame> get_selected() const noexcept;
    };
}