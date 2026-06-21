#include <string_view>
#include <raylib.h>

namespace nebula_salvage {
    
class Texture {
    public:
        Texture(std::string_view path);
        Texture(const Texture&) = delete;
        Texture(Texture&&) noexcept;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture) noexcept;
        ~Texture() noexcept;

        friend void swap(Texture& a, Texture& b) noexcept;
    private:
        ::Texture texture;
};

inline void swap(Texture& a, Texture& b) noexcept {
    std::swap(a.texture, b.texture);
}

}
