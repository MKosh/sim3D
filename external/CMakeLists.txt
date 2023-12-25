
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

#-------------------------------------------------------------------------------
# glfw
add_compile_definitions(GLFW_BUILD_DOCS=OFF)
add_subdirectory(glfw)

#-------------------------------------------------------------------------------
# spdlog
add_subdirectory(spdlog)

#-------------------------------------------------------------------------------
# glm
add_subdirectory(glm)
