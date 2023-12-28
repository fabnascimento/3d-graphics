cmake_minimum_required(VERSION 3.27)
project(3d_graphics C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 CONFIG REQUIRED)

add_executable(3d_graphics src/main.c
        src/display.c
        src/display.h
        src/vector.c
        src/vector.h
        src/mesh.c
        src/mesh.h
        src/triangle.c
        src/triangle.h)

target_link_libraries(3d_graphics
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
