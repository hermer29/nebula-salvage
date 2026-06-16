#include <assert.h>
#include <raylib.h>
#include <chrono>
#include <format>

using namespace std::chrono;

int main() {

    InitWindow(800, 600, "Nebula Salvage");
    float deltaTime;
    auto previousTime = high_resolution_clock::now();
    
    bool isFirstFrame = true;
    while(!WindowShouldClose()){
        auto end = high_resolution_clock::now();
        deltaTime = duration<float>(end - previousTime).count();
        if (!isFirstFrame) {
            assert(deltaTime > 0.0f);
        }
        isFirstFrame = false;
        previousTime = high_resolution_clock::now();
        assert(!WindowShouldClose());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        
        
        DrawText(std::format("fps2: {}, FPS {}, dt: {}, ", GetFPS(), (1.0f / deltaTime), deltaTime).c_str(), 10, 10, 20, RED);
        
    

        EndDrawing();
        
    }

    return 0;
}

