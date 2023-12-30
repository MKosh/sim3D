
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glad/CMakeLists.txt" 
   OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/imgui/CMakeLists.txt"
   OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/assimp/CMakeLists.txt"
   OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt"
   OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/spdlog/CMakeLists.txt"
   OR NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glm/CMakeLists.txt"
)
  message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
  

#-------------------------------------------------------------------------------
# glad
add_subdirectory(glad)

#-------------------------------------------------------------------------------
# imgui
add_subdirectory(imgui)

#-------------------------------------------------------------------------------
# assimp
add_subdirectory(assimp)

# message(STATUS " ")
# message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
# FetchContent_Declare(
#   assimp2
#   GIT_REPOSITORY https://github.com/assimp/assimp.git
#   GIT_TAG master
#   SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/assimp2
#   BINARY_DIR ${CMAKE_BINARY_DIR}/external/assimp2
# )
# FetchContent_MakeAvailable(assimp2)
# # file(COPY_FILE ${assimp_BINARY_DIR}/bin/libassimp-5.dll ${CMAKE_BINARY_DIR}/libassimp-5.dll)
# message(STATUS "assimp source = ${assimp2_SOURCE_DIR}/ assimp bin = ${assimp2_BINARY_DIR}")

#-------------------------------------------------------------------------------
# glfw
add_compile_definitions(GLFW_BUILD_DOCS=OFF)
add_subdirectory(glfw)
# FetchContent_Declare(
#   glfw
#   GIT_REPOSITORY https://github.com/glfw/glfw.git
#   GIT_TAG master
# )
# FetchContent_MakeAvailable(glfw)
# # file(COPY_FILE ${glfw_BINARY_DIR}/src/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll)
# message(STATUS "glfw source = ${glfw_SOURCE_DIR}/ glfw bin = ${glfw_BINARY_DIR}")


#-------------------------------------------------------------------------------
# spdlog
add_subdirectory(spdlog)

#-------------------------------------------------------------------------------
# glm
add_subdirectory(glm)
