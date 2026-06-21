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
            Sound& operator=(Sound);
            ~Sound() noexcept;

        private:
            ::Sound sound;
    };
}