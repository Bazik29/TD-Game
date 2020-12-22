cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


set (BIN ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set (DLL ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DLL}) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB}) 



# libraries

#GLM
add_subdirectory(lib/glm)

#JSON
add_subdirectory(lib/nlohmann_json)

# GLFW
set(BUILD_SHARED_LIBS ON)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

add_subdirectory(lib/glfw)



# gl
add_library(gl STATIC src/gl/gl_core_4_3.hpp src/gl/gl_core_4_3.cpp)
target_include_directories(gl INTERFACE src/gl/)

# filesystem fix
include_directories(src/fs/)


# GAME_LOGIC
set(GAME_LOGIC_HPP 
	src/BattleObjects.hpp
	src/BattleManager.hpp
	src/ResourceManager.hpp
)
set(GAME_LOGIC_CPP 
	src/BattleObjects.cpp
	src/BattleManager.cpp
	src/ResourceManager.cpp
)

add_library(game_logic STATIC ${GAME_LOGIC_HPP} ${GAME_LOGIC_CPP})
target_include_directories(game_logic INTERFACE src)
target_link_libraries(game_logic glm::glm nlohmann_json::nlohmann_json)

if(NOT MSVC)
	target_link_libraries(game_logic stdc++fs)
endif()


# GAME_GRAPHICS
set(GAME_GRAPHICS_HPP
	src/WindowGLFW.hpp
	src/Input.hpp
	src/GLSLProgram.hpp
	src/Renderer.hpp
)
set(GAME_GRAPHICS_CPP
	src/WindowGLFW.cpp
	src/Input.cpp
	src/GLSLProgram.cpp
	src/Renderer.cpp
)

add_library(game_graphics STATIC ${GAME_GRAPHICS_HPP} ${GAME_GRAPHICS_CPP})
target_include_directories(game_graphics INTERFACE src)
target_link_libraries(game_graphics glm::glm opengl32 gl glfw)


# executable
add_executable(${PROJECT_NAME} src/target/main.cpp)
target_link_libraries(${PROJECT_NAME} game_logic game_graphics)
