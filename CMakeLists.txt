cmake_minimum_required(VERSION 3.9)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
project(nibbler)

set(SOURCE_EXE
        src/main.cpp
        inc/Game.hpp
        src/Game.cpp
        nibbler_glfw/inc/nibbler_glfw.hpp
        nibbler_glfw/src/nibbler_glfw.cpp
        nibbler_glfw/inc/Shader.hpp
        nibbler_glfw/src/Shader.cpp
        nibbler_glfw/inc/Texture.hpp
        nibbler_glfw/src/Texture.cpp
        nibbler_glfw/inc/CustomException.hpp
        nibbler_glfw/inc/ResourceManager.hpp
        nibbler_glfw/src/ResourceManager.cpp
        nibbler_glfw/inc/Drawer.hpp
        nibbler_glfw/src/Drawer.cpp
        nibbler_glfw/inc/SpriteRenderer.hpp
        nibbler_glfw/src/SpriteRenderer.cpp
        nibbler_glfw/inc/SpriteRenderer.hpp
        nibbler_glfw/src/SpriteRenderer.cpp
        inc/GameObject.hpp
        src/GameObject.cpp
        src/GameLevel.cpp
        inc/GameLevel.hpp src/Snake.cpp inc/Snake.hpp)

add_executable(nibbler ${SOURCE_EXE})

target_link_libraries(nibbler)

include_directories(inc/
        nibbler_glfw/inc
        nibbler_glfw/lib/glad/build/include/
        nibbler_glfw/lib/glfw/include
        nibbler_glfw/lib/stb/
        nibbler_glfw/lib/glm/
                    )