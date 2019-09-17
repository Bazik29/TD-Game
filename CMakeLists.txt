cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#set(BUILD_SHARED_LIBS ON)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(lib/glfw)

#add_definitions(-DGLFW_DLL)
add_definitions(-DGLFW_INCLUDE_NONE)

add_subdirectory(lib/glm)

set(BUILD_SHARED_LIBS ON)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_NO_EXPORT ON)
add_subdirectory(lib/assimp)

include_directories(lib/glfw/include/
                    lib/glm/
                    lib/assimp/include/
                    lib/stb/
                    src/)
                  
file(GLOB ENGINE_SOURCES src/*.cpp)

add_library(engine STATIC ${ENGINE_SOURCES})

if(MSVC)
    target_link_libraries(engine opengl32 glfw assimp)
else()
    target_link_libraries(engine opengl32 glfw assimp stdc++fs)
endif()

add_executable(${PROJECT_NAME} src/target/main.cpp)
target_link_libraries(${PROJECT_NAME} engine)
