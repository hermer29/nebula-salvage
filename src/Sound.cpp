#include "Sound.hpp"
#include "raylib.h"
#include <string_view>

namespace nebula_salvage {


    Sound::Sound(std::string_view s) {
        sound = LoadSound(s.data());
    }

    Sound::~Sound() noexcept {
        if(sound.stream.buffer != nullptr)
        {
            UnloadSound(this->sound);
        }
    }

    Sound::Sound(Sound&& s) noexcept {
        swap(*this, s);
    }

    Sound& Sound::operator=(Sound s) noexcept {
        swap(*this, s);
        return *this;
    }





}