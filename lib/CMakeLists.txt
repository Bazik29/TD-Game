cmake_minimum_required(VERSION 3.8)

# GLFW
set(BUILD_SHARED_LIBS OFF)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

add_subdirectory(glfw)

#Assimp
set(BUILD_SHARED_LIBS ON)

option(ASSIMP_BUILD_ASSIMP_TOOLS "If the supplementary tools for Assimp are built in addition to the library." OFF)
option(ASSIMP_BUILD_TESTS "If the test suite for Assimp is built in addition to the library." OFF)
option(ASSIMP_NO_EXPORT "Disable Assimp's export functionality." ON)

#AMF 3DS AC ASE ASSBIN B3D BVH COLLADA DXF CSM HMP IRRMESH IRR LWO LWS MD2 MD3 MD5 MDC MDL NFF NDO OFF OGRE OPENGEX PLY MS3D COB BLEND IFC XGL FBX Q3D Q3BSP RAW SIB SMD STL TERRAGEN 3D X X3D GLTF 3MF MMD STEP
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)

add_subdirectory(assimp)

#GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/glm")

#STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb")

#LuaBridge
add_subdirectory(LuaBridge/Source)


# Lua 5.2, C++11  (from LuaBridge/Tests/Lua/Lua.5.2.0)
set(LUABRIDGE_TEST_LUA52_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/LuaBridge/Tests/Lua/LuaLibrary.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/LuaBridge/Tests/Lua/LuaLibrary5.2.0.cpp"
)

add_library(Lua52 STATIC ${LUABRIDGE_TEST_LUA52_FILES})

target_compile_options(Lua52
  PUBLIC -DLUABRIDGEDEMO_LUA_VERSION=502
)

target_include_directories(Lua52 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/LuaBridge/Tests/")
