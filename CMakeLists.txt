cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


set(OPENGL_LIB GL)
# set(OPENGL_LIB opengl32)

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
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
add_subdirectory(lib/nlohmann_json)

# GLFW
set(BUILD_SHARED_LIBS ON)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

add_subdirectory(lib/glfw)

# gl
add_library(gl_core STATIC src/gl_core/gl_core_4_3.hpp src/gl_core/gl_core_4_3.cpp)
target_include_directories(gl_core INTERFACE src/gl_core/)
target_link_libraries(gl_core ${OPENGL_LIB})


# filesystem fix
include_directories(src/utils/)


# GAME_LOGIC
set(GAME_LOGIC_HPP
	src/managers/BattleManager.hpp
	src/managers/ResourceManager.hpp
	src/managers/ResourceManager.hpp

	src/gameObjects/Enemy.hpp
	src/gameObjects/EnemyEntity.hpp
	src/gameObjects/EnemyQueue.hpp
	src/gameObjects/Level.hpp
	src/gameObjects/MeshGL.hpp
	src/gameObjects/Way.hpp
)
set(GAME_LOGIC_CPP 
	src/managers/BattleManager.cpp
	src/managers/ResourceManager.cpp
)

add_library(game_logic STATIC ${GAME_LOGIC_HPP} ${GAME_LOGIC_CPP})
target_include_directories(game_logic INTERFACE src)
target_link_libraries(game_logic gl_core glm::glm nlohmann_json::nlohmann_json)

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
target_link_libraries(game_graphics glm::glm gl_core glfw)

# executable
add_executable(${PROJECT_NAME} src/target/main.cpp)
target_link_libraries(${PROJECT_NAME} game_logic game_graphics)
