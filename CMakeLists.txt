cmake_minimum_required(VERSION 3.22)

#-------------------------------------------------------------------------------
# Set basic cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

#-------------------------------------------------------------------------------
# Setup project and executable
project(sim3D LANGUAGES C CXX)
add_executable(simulation src/main.cc)

#-------------------------------------------------------------------------------
# Confirm OpenGL is available
find_package(OpenGL REQUIRED)

#-------------------------------------------------------------------------------
# Set up external dependencies. Most are git submodules, they should be pulled
# and updated before being built.
add_subdirectory(external)

#-------------------------------------------------------------------------------
# Add Core library for basic application and windowing functionality, includes
# Dear ImGui for basic UI interaction
add_library(core STATIC)
add_subdirectory(src/Core)

#-------------------------------------------------------------------------------
# Add Renderer library for model loading and displaying visuals
add_library(renderer STATIC)
add_subdirectory(src/Renderer)

#-------------------------------------------------------------------------------
# Determine the system and build appropriately
message(STATUS "Building for system: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

  target_include_directories(simulation PUBLIC 
    external
    external/glad
    external/imgui
    external/assimp
    external/spdlog
    external/glm
  )

  target_include_directories(core PUBLIC 
    external
    external/glad
    external/imgui
    src
  )

  target_link_libraries(core PRIVATE 
    glfw
    imgui
    assimp
    glad
    renderer
    spdlog::spdlog
  )

  target_include_directories(renderer PUBLIC 
    external
    external/glad
    external/imgui
    src
  )

  target_link_libraries(renderer PRIVATE 
    glfw
    imgui
    assimp
    glad
    spdlog::spdlog
  )

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

  target_include_directories(simulation PUBLIC 
    external/include
    external
    /ucrt64/include
    /mingw64/include
  )

  target_include_directories(core PUBLIC 
    external/include
    src
    external
    /ucrt64/include
    /mingw64/include
  )

  target_link_libraries(core PRIVATE 
    glfw
    opengl32
    imgui
    assimp
    glad
    spdlog::spdlog
  )

  target_include_directories(renderer PUBLIC 
    external/include
    src
    external
    /ucrt64/include
    /mingw64/include
  )

  target_link_libraries(renderer PRIVATE 
    glfw
    opengl32
    imgui
    assimp
    glad
    spdlog::spdlog
  )

endif()

#-------------------------------------------------------------------------------
# Link required libraries for the main executable
target_link_libraries(simulation PRIVATE 
  glfw 
  assimp 
  imgui 
  glad 
  core 
  renderer 
  spdlog::spdlog
)

set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
target_compile_options(simulation PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(simulation PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
