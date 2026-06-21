#include "Texture.hpp"
#include <string_view>
#include <raylib.h>

namespace nebula_salvage {

Texture::Texture(std::string_view path) {
    texture = LoadTexture(path.data());
}

Texture::Texture(Texture&& other) noexcept {
    swap(*this, other);
};

Texture& Texture::operator=(Texture other) noexcept {
    swap(*this, other);
    return *this;
}

Texture::~Texture() noexcept {
    if(texture.id != 0)
        UnloadTexture(texture);
}

}

