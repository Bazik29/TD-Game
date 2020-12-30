cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	set(OPENGL_LIB opengl32)
endif (WIN32)

if (UNIX)
	set(OPENGL_LIB GL)
endif (UNIX)


set (BIN ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set (DLL ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DLL}) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB}) 

# library

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.3.2
)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 0.9.9.8
)

FetchContent_Declare(
	json
	GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
	GIT_TAG v3.9.1
)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# gl_core
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
	src/gameObjects/EnemyWay.hpp

	src/gameObjects/Tower.hpp
	src/gameObjects/TowerEntity.hpp
	src/gameObjects/BattleGrid.hpp
)
set(GAME_LOGIC_CPP 
	src/managers/BattleManager.cpp
	src/managers/ResourceManager.cpp

	src/gameObjects/EnemyQueue.cpp
	src/gameObjects/MeshGL.cpp
	src/gameObjects/EnemyWay.cpp

	src/gameObjects/BattleGrid.cpp
)

add_library(game_logic STATIC ${GAME_LOGIC_HPP} ${GAME_LOGIC_CPP})
target_include_directories(game_logic INTERFACE src)
target_link_libraries(game_logic gl_core glm::glm nlohmann_json::nlohmann_json)

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

target_compile_options(game_logic PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(game_graphics PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
