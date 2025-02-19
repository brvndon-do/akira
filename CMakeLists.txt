cmake_minimum_required(VERSION 3.10)
project(akira LANGUAGES C)

# Set C standard (optional but recommended)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable with source files
add_executable(${PROJECT_NAME}
    src/main.c
    src/event_handler.c
)

# Include directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)