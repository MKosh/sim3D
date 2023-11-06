cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 20)

project(sim3D LANGUAGES C CXX)
add_executable(simulation src/main.cc)

set(CMAKE_TOOLCHAIN_FILE "/home/markm/packages/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_PREFIX_PATH "/home/markm/packages/vcpkg/packages/sfml_x64-linux")
find_package(SFML COMPONENTS system window CONFIG REQUIRED)
set(SFML_INCLUDE_DIRS "/home/markm/packages/vcpkg/packages/sfml_x64-linux/include/")
target_include_directories(simulation PUBLIC ${SFML_INCLUDE_DIRS} external/include/ external assimp-5.2.5/include)

add_subdirectory(external)

add_library(graphics src/Camera/Camera.cc src/Input/Input.cc src/App/App.cc src/Shader/Shader.cc src/Model/Mesh.cc src/Model/Model.cc src/Model/Box.cc external/imgui/imgui.cpp external/imgui/imgui-SFML.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp)
target_include_directories(graphics PUBLIC external/include ${SFML_INCLUDE_DIRS} src external)
target_link_libraries(graphics PRIVATE sfml-system sfml-window sfml-graphics)

# add_library(imgui external/imgui/imgui.cpp external/imgui/imgui-SFML.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp)
# target_include_directories(imgui PUBLIC external/imgui external/include)
# target_link_libraries(imgui PRIVATE sfml-system sfml-window sfml-graphics)
# message(STATUS ${CMAKE_HOME_DIRECTORY})

target_link_libraries(simulation PRIVATE sfml-system sfml-window sfml-graphics dl assimp glad graphics)

set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
target_compile_options(simulation PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(simulation PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
