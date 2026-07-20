#include <string_view>
#include <raylib.h>

namespace nebula_salvage {

    class Music {
        public:
            Music(std::string_view);

            Music(const Music&) = delete;
            Music& operator=(const Music&) = delete;

            Music(Music&&) noexcept;
            Music& operator=(Music) noexcept;

            ~Music() noexcept;

            void play();
            void stop();
            void update();

        private:
            ::Music music = {};  
            friend void swap(Music&, Music&) noexcept;
    };

    inline void swap(Music& a, Music& b) noexcept {
        std::swap(a.music, b.music);
    }
}