#include <string_view>
#include <raylib.h>

class Tex {
    public:
        Tex(std::string_view path);
        Tex(const Tex&) = delete;
        Tex(Tex&&) noexcept;
        Tex& operator=(const Tex&) = delete;
        Tex& operator=(Tex) noexcept;
        ~Tex() noexcept;

        friend void swap(Tex& a, Tex& b) noexcept;
    private:
        Texture2D texture;
};

inline void swap(Tex& a, Tex& b) noexcept {
    std::swap(a.texture, b.texture);
}