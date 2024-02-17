add_library(utils STATIC)
target_sources(utils PUBLIC Utils.cc)
target_include_directories(utils PUBLIC ./ ${CMAKE_SOURCE_DIR}/external/glad ${CMAKE_SOURCE_DIR}/external)
target_link_libraries(utils PRIVATE glad imgui)
