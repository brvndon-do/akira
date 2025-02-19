cmake_minimum_required(VERSION 3.10)
project(akira LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.c
    src/event_handler.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

# SDL3 configuration (Arch Linux-specific fix)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

# Link SDL3 and system dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL3_LIBRARIES}
    m       # Math library
    dl      # Dynamic loader
    pthread # Thread support
    rt      # Real-time extensions (optional)
)
