cmake_minimum_required(VERSION 3.9)
project(Nibbler)

set(SOURCE_EXE
        nibbler_glfw/inc/nibbler_glfw.hpp
        nibbler_glfw/src/nibbler_glfw.cpp
        nibbler_glfw/inc/Shader.hpp
        nibbler_glfw/src/Shader.cpp
        nibbler_glfw/inc/Texture.hpp
        nibbler_glfw/src/Texture.cpp
        nibbler_glfw/inc/CustomException.hpp

   )

#set(SOURCE_LIB lib_dyn1/src/test.cpp lib_dyn2/src/API2.cpp lib_dyn2/src/game.cpp)

#add_library(SHARED ${SOURCE_LIB})

add_executable(Nibbler ${SOURCE_EXE})

target_link_libraries(Nibbler)

include_directories(inc/ nibbler_glfw/inc nibbler_glfw/libGlew/inc nibbler_glfw/stb/ nibbler_glfw/glm/)