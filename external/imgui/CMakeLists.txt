add_library(imgui STATIC imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_opengl3.cpp imgui_impl_glfw.cpp imgui_demo.cpp)
target_include_directories(imgui PRIVATE ./)
