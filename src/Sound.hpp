#include <string_view>
#include <raylib.h>

namespace nebula_salvage
{
    class Sound
    {
        public:
            Sound(std::string_view name);
            Sound(Sound&&) noexcept;
            Sound(const Sound&) = delete;
            Sound& operator=(const Sound&) = delete;
            Sound& operator=(Sound) noexcept;
            ~Sound() noexcept;

        private:
            ::Sound sound{};
            friend void swap(Sound& a, Sound& b) noexcept;
    };

    inline void swap(Sound& a, Sound& b) noexcept {
        std::swap(a.sound, b.sound);
    }
}