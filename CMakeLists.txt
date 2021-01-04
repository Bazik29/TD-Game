cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(COMPILE_FLAGS -Wall -Wextra -Wpedantic)

include(FetchContent)


if (WIN32)
	set(OPENGL_LIB opengl32)
endif (WIN32)

if (UNIX)
	set(OPENGL_LIB GL)
endif (UNIX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib) 


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

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

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

# utils
add_library(utils INTERFACE)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/utils)

# GAME_SRC
set(GAME_SRC_HPP
	src/gameObjects/BattleGridEntity.hpp
	src/gameObjects/Enemy.hpp
	src/gameObjects/EnemyEntity.hpp
	src/gameObjects/EnemyQueue.hpp
	src/gameObjects/EnemyWay.hpp
	src/gameObjects/Level.hpp
	src/gameObjects/ShellEntity.hpp
	src/gameObjects/Tower.hpp
	src/gameObjects/TowerEntity.hpp

	src/logicObjects/EnemyProperty.hpp
	src/logicObjects/ShellProperty.hpp
	src/logicObjects/TowerProperty.hpp

	src/managers/BattleManager.hpp
	src/managers/ResourceManager.hpp
	src/managers/GameManager.hpp

	src/renderObjects/BattleGridMeshGl.hpp
	src/renderObjects/ElementsMeshGl.hpp
	src/renderObjects/MeshGl.hpp
	
	src/GLSLProgram.hpp
	src/Input.hpp
	src/Renderer.hpp
	src/WindowGLFW.hpp
)

set(GAME_SRC_CPP
	src/gameObjects/BattleGridEntity.cpp
	src/gameObjects/Enemy.cpp
	src/gameObjects/EnemyEntity.cpp
	src/gameObjects/EnemyQueue.cpp
	src/gameObjects/EnemyWay.cpp
	src/gameObjects/ShellEntity.cpp
	src/gameObjects/Tower.cpp
	src/gameObjects/TowerEntity.cpp

	src/logicObjects/EnemyProperty.cpp
	src/logicObjects/ShellProperty.cpp
	src/logicObjects/TowerProperty.cpp

	src/managers/BattleManager.cpp
	src/managers/ResourceManager.cpp
	src/managers/GameManager.cpp


	src/renderObjects/BattleGridMeshGl.cpp
	src/renderObjects/ElementsMeshGl.cpp
	src/renderObjects/MeshGl.cpp

	src/GLSLProgram.cpp
	src/Input.cpp
	src/Renderer.cpp
	src/WindowGLFW.cpp
)

set(GAME_SRC_INC
	src
)

add_library(game_src STATIC ${GAME_SRC_HPP} ${GAME_SRC_CPP})
target_include_directories(game_src PUBLIC ${GAME_SRC_INC})
target_link_libraries(game_src utils gl_core glm::glm glfw nlohmann_json::nlohmann_json)

add_executable(${PROJECT_NAME} ${TARGER_SRC} src/target/main.cpp)
target_link_libraries(${PROJECT_NAME} game_src)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})
