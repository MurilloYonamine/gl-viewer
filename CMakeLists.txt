cmake_minimum_required(VERSION 3.10)

project(gl_viewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/window.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        GLEW::GLEW
        assimp::assimp
)