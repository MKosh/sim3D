cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

project(sim3D LANGUAGES C CXX)
add_executable(simulation src/main.cc)

find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(external)

add_library(core STATIC)
add_subdirectory(src/Core)

add_library(renderer STATIC)
add_subdirectory(src/Renderer)

message(STATUS ${CMAKE_SYSTEM_NAME})
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  # set(CMAKE_C_COMPILER /usr/bin/clang)
  # set(CMAKE_CXX_COMPILER /usr/bin/clang++)

  target_include_directories(simulation PUBLIC external external/glad external/imgui assimp-5.2.5/include)

  target_include_directories(core PUBLIC external external/glad external/imgui src)
  target_link_libraries(core PRIVATE glfw imgui assimp glad renderer spdlog::spdlog)

  target_include_directories(renderer PUBLIC external external/glad external/imgui src)
  target_link_libraries(renderer PRIVATE glfw imgui assimp glad spdlog::spdlog)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  # set(CMAKE_C_COMPILER C:/msys64/ucrt64/bin/clang)
  # set(CMAKE_CXX_COMPILER C:/msys64/ucrt64/bin/clang++)

  target_include_directories(simulation PUBLIC external/include/ external /ucrt64/include /mingw64/include)

  target_include_directories(core PUBLIC external/include src external /ucrt64/include /mingw64/include)
  target_link_libraries(core PRIVATE glfw opengl32 imgui assimp glad spdlog::spdlog)

  target_include_directories(renderer PUBLIC external/include src external /ucrt64/include /mingw64/include)
  target_link_libraries(renderer PRIVATE glfw opengl32 imgui assimp glad spdlog::spdlog)
endif()


target_link_libraries(simulation PRIVATE glfw assimp imgui glad core renderer spdlog::spdlog)

set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
target_compile_options(simulation PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(simulation PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
