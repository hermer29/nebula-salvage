#include "Music.hpp"
#include "raylib.h"

namespace nebula_salvage {

Music::Music(std::string_view s) {
    music = LoadMusicStream(s.data());
}

Music::~Music() noexcept {
    if(music.stream.buffer == nullptr) {
        return;
    }

    UnloadMusicStream(music);
}

Music& Music::operator=(Music m) noexcept {
    swap(*this, m);
    return *this;   
}

Music::Music(Music&& m) noexcept {
    swap(*this, m);
}

void Music::play() {
    PlayMusicStream(music);
}

void Music::stop() {
    StopMusicStream(music);
}

void Music::update() {
    UpdateMusicStream(music);
}

}