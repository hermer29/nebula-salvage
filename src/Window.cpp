#include <raylib.h>
#include <string_view>

#include "Window.hpp"

namespace nebula_salvage {

Window::Window(int width, int height, const std::string_view title) : 
    width(width), height(height), title(title) {
    InitWindow(width, height, title.data());
}

Window::~Window() {
    CloseWindow();
}

bool Window::shouldClose() const {
    return WindowShouldClose();
}

}
