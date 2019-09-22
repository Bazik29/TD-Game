cmake_minimum_required(VERSION 3.8)

project(td-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
#set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set (BIN ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set (DLL ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
#set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DLL}) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}) 
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB}) 

add_subdirectory(lib)

file(GLOB ENGINE_SOURCES "src/*.cpp")

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(engine STATIC ${ENGINE_SOURCES})

target_include_directories(
	engine PUBLIC
		lib/glfw/include/
        lib/assimp/include/
		lib/LuaBridge/Source/LuaBridge/
#		lib/LuaBridge/Tests/Lua/Lua.5.2.0/src/
		lib/LuaBridge/Tests/Lua/
        src/)

target_link_libraries(engine opengl32 glfw glm assimp stb)
if(NOT MSVC)
    target_link_libraries(engine stdc++fs)
endif()

add_executable(${PROJECT_NAME} src/target/main.cpp)

target_link_libraries(${PROJECT_NAME} engine LuaBridge Lua52)
