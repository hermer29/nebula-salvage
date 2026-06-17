#include <string_view>

namespace nebula_salvage {

class Window {
    public:
        Window(int width, int height, const std::string_view title);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        bool shouldClose() const;
    private:
        int width;
        int height;
        std::string_view title;
};
}