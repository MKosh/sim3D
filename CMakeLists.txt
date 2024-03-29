cmake_minimum_required(VERSION 3.22)

#-------------------------------------------------------------------------------
# Set basic cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
#-------------------------------------------------------------------------------
# Setup project and executable
project(sim3D LANGUAGES C CXX)
add_executable(sim3D src/main.cc)

#-------------------------------------------------------------------------------
# Confirm OpenGL is available
find_package(OpenGL REQUIRED)

#-------------------------------------------------------------------------------
# Set up external dependencies. Most are git submodules, they should be pulled
# and updated before being built.
# add_library(assimp STATIC)
# add_library(glfw STATIC)
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
# Add utility library
add_subdirectory(src/Utils)

#-------------------------------------------------------------------------------
# Add Simulation library
add_subdirectory(src/Simulation)

#-------------------------------------------------------------------------------
# Determine the system and build appropriately
message(STATUS "Building for system: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

  target_include_directories(sim3D PUBLIC 
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
    utils
    simulation
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
  message(STATUS "Building for windows on windows")

  target_include_directories(sim3D PUBLIC 
    external/include
    external
  )

  target_include_directories(core PUBLIC 
    external/include
    src
    external
  )

  target_link_libraries(core PRIVATE 
    glfw
    opengl32
    imgui
    assimp
    glad
    spdlog::spdlog
    utils
    simulation
  )

  target_include_directories(renderer PUBLIC 
    external/include
    src
    external
  )

  target_link_libraries(renderer PRIVATE 
    glfw
    opengl32
    imgui
    assimp
    glad
    spdlog::spdlog
  )

  add_custom_command(TARGET sim3D POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_BINARY_DIR}/external/assimp/bin/libassimp-5.dll ${CMAKE_BINARY_DIR})

  add_custom_command(TARGET sim3D POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_BINARY_DIR}/external/glfw/src/glfw3.dll ${CMAKE_BINARY_DIR})

  add_custom_command(TARGET sim3D POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

endif()

#-------------------------------------------------------------------------------
# Link required libraries for the main executable
target_link_libraries(sim3D PRIVATE 
  glfw 
  assimp 
  imgui 
  glad 
  core 
  renderer 
  utils
  simulation
  spdlog::spdlog
)


message(STATUS "Cmake binary dir: ${CMAKE_BINARY_DIR}")
message(STATUS "Project binary dir: ${PROJECT_BINARY_DIR}")
set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-g;-DMYDEBUG") #-Werror;
set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
target_compile_options(sim3D PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(sim3D PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")

find_library(myglfwlib glfw
  NAMES
    glfw3
  PATHS
    "build/msys/Release/external/glfw/src"
    "${CMAKE_BINARY_DIR}/_deps/glfw-build/src"
    "external/glfw/src"
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_DEFAULT_PATH
)
find_library(myassimplib assimp 
  PATHS
    "build/msys/Release/external" 
    "build/msys/Release/external/assimp" 
    "build/msys/Release/external/assimp/bin" 
    "external/assimp/bin"
    "${CMAKE_BINARY_DIR}/external/assimp/bin"
    "${CMAKE_BINARY_DIR}/_deps/assimp-build/bin"
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_DEFAULT_PATH
)
message(STATUS "GLFW lib dir: ${myglfwlib}")
message(STATUS "ASSIMP lib dir: ${myassimplib}")
