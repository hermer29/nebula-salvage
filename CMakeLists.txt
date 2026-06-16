cmake_minimum_required(VERSION 4.3)

# Включаем санитайзеры

include(cmake/Sanitizers.cmake)
enable_sanitizers(nebula_salvage)

# Проект

project(nebula_salvage)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})


# Грузим все заголовки в переменную hdrs и cpp в srcs
file(GLOB hdrs "src/*.h")
file(GLOB srcs "src/*.cpp")

# компилим все исходники
add_executable(nebula_salvage ${srcs} ${hdrs})


# Флаги компилятора

target_compile_options(nebula_salvage PRIVATE 
	-Wall -Wextra -Wpedantic -Werror
)

# Загружаем Raylib через FetchContent

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)


target_link_libraries(nebula_salvage PRIVATE raylib)

### 
