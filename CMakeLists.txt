cmake_minimum_required(VERSION 4.3)

project(gl_viewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(gl_viewer
        src/main.cpp
        src/window.cpp
)

target_link_libraries(gl_viewer PRIVATE
        glfw
        glad::glad
)