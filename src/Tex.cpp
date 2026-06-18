#include "Tex.hpp"
#include <string_view>
#include <raylib.h>

Tex::Tex(std::string_view path) {
    texture = LoadTexture(path.data());
}

Tex::Tex(Tex&& other) noexcept {
    swap(*this, other);
};

Tex& Tex::operator=(Tex other) noexcept {
    swap(*this, other);
    return *this;
}

Tex::~Tex() noexcept {
    if(texture.id != 0)
        UnloadTexture(texture);
}