#include "../header/input.h"

namespace Crimson::Input{

GLFWwindow* window = nullptr;
bool mouse_down = false;
glm::ivec2 mouse_position = glm::ivec2(0);
glm::vec2 mouse_delta = glm::vec2(0);
bool keys[InputKeyCount] = { false };
bool buttons[InputButtonCount] = { false };
bool prevKeys[InputKeyCount] = { false };
bool prevButtons[InputButtonCount] = { false };

void listen()
{
    assert(window != nullptr);
    glfwPollEvents();

    double _x, _y;
    int h;

    glfwGetCursorPos(window, &_x, &_y);
    glfwGetWindowSize(window, 0, &h);

    mouse_delta.x = _x - mouse_position.x;
    mouse_delta.y = _y - mouse_position.y;

    mouse_position.x = (int)_x;
    mouse_position.y = (int)_y;

    // Keys
    for(unsigned int i = 0; i < InputKeyCount; i ++)
    {
        prevKeys[i] = keys[i];
        keys[i] = glfwGetKey(window, i);
    }
    
    // Mouse buttons
    for(unsigned int i = 0; i < InputButtonCount; i ++)
    {
        prevButtons[i] = buttons[i];
        buttons[i] = glfwGetMouseButton(window, i);
    }
}

bool is_key_down(Key key)
{
    assert(window != nullptr);
    assert((int)key >= 0 && (int)key < InputKeyCount);

    return keys[(int)key];
}

bool is_key_pressed(Key key)
{
    assert(window != nullptr);
    assert((int)key >= 0 && (int)key < InputKeyCount);

    return keys[(int)key] == true && prevKeys[(int)key] == false;
}

bool is_key_released(Key key)
{
    assert(window != nullptr);
    assert((int)key >= 0 && (int)key < InputKeyCount);

    return keys[(int)key] == false && prevKeys[(int)key] == true;
}

bool is_mouse_down(MouseButton button)
{
    assert(window != nullptr);
    assert((int)button >= 0 && (int)button < InputButtonCount);

    return buttons[(int)button];
}

bool is_mouse_pressed(MouseButton button)
{
    assert(window != nullptr);
    assert((int)button >= 0 && (int)button < InputButtonCount);

    return buttons[(int)button] == true && prevButtons[(int)button] == false;
}

bool is_mouse_released(MouseButton button)
{
    assert(window != nullptr);
    assert((int)button >= 0 && (int)button < InputButtonCount);

    return buttons[(int)button] == false && prevButtons[(int)button] == true;
}
} // namespace Crimson::Input
