add_library(simulation STATIC)
target_sources(simulation PUBLIC Simulation.cc)
target_include_directories(simulation PUBLIC ./ ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/external)
