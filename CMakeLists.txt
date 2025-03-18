cmake_minimum_required(VERSION 3.10)
project(akira LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.c
    src/system.c
    src/system.h
    src/event_handler.c
    src/event_handler.h
    src/app.c
    src/app.h
    src/entity.c
    src/entity.h
    src/game.c
    src/game.h
    src/input.c
    src/input.h
    src/enums.h
    src/structs.h
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${SDL3_LIBRARIES}
    m dl pthread rt
)