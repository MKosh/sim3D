cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 20)

project(sim3D LANGUAGES C CXX)
add_executable(simulation src/main.cc)

find_package(glfw3 REQUIRED)
target_include_directories(simulation PUBLIC external/include/ external assimp-5.2.5/include)

add_subdirectory(external)

add_library(imgui STATIC external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_impl_opengl3.cpp external/imgui/imgui_impl_glfw.cpp external/imgui/imgui_demo.cpp)
target_include_directories(imgui PUBLIC external/imgui external/include)
# target_link_libraries(imgui PRIVATE sfml-system sfml-window graphics glad dl GL udev)
target_link_libraries(imgui PRIVATE glfw glad dl GL udev)
# message(STATUS ${CMAKE_HOME_DIRECTORY})

# add_library(core STATIC src/App/Entity.cc src/App/Component.cc)
# target_include_directories(core PUBLIC src external)

add_library(graphics STATIC src/Camera/Camera.cc src/Input/InputHandler.cc src/App/App.cc src/App/Window.cc src/Shader/Shader.cc src/Model/Mesh.cc src/Model/Model.cc src/Model/Box.cc) # external/imgui/imgui.cpp external/imgui/imgui-SFML.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_demo.cpp)
target_include_directories(graphics PUBLIC external/include ${SFML_INCLUDE_DIRS} src external)
# target_link_libraries(graphics PRIVATE sfml-system sfml-window sfml-graphics udev) # TGUI::TGUI)
target_link_libraries(graphics PRIVATE glfw imgui)
# message(STATUS ${SFML_INCLUDE_DIRS})


target_link_libraries(simulation PRIVATE glfw dl assimp imgui glad graphics udev) # TGUI::TGUI)

set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
target_compile_options(simulation PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(simulation PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
# ---
# find_package(glfw3 REQUIRED)
# target_include_directories(simulation PUBLIC external/include/ external assimp-5.2.5/include)
#
# add_subdirectory(external)
#
# add_library(graphics STATIC src/Camera/Camera.cc src/Input/InputHandler.cc src/App/App.cc src/Shader/Shader.cc src/Model/Mesh.cc src/Model/Model.cc src/Model/Box.cc) # external/imgui/imgui.cpp external/imgui/imgui-SFML.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_demo.cpp)
# target_include_directories(graphics PUBLIC external/include src external)
# target_link_libraries(graphics PRIVATE glad)
#
# add_library(imgui STATIC external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_impl_opengl3.cpp external/imgui/imgui_impl_glfw.cpp external/imgui/imgui_demo.cpp)
# target_include_directories(imgui PUBLIC external/imgui external/include)
# target_link_libraries(imgui PRIVATE graphics glad dl GL udev)
#
# target_link_libraries(simulation PRIVATE dl assimp imgui glad graphics glfw udev)
#
# set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
# set(RELEASE_OPTIONS "-Wall;-Wextra;-Wpedantic;-O3")
# target_compile_options(simulation PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
# target_compile_options(simulation PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
