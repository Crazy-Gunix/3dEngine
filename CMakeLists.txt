# Copyright 2022 Jacob Gibson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http:#www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.20.0)

project(3dEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")

set(ENGINE_VERSION_PHASE "alpha")

configure_file(config/version.h.in config/version.h)

# Project source
add_subdirectory(src)



find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/assimp/CMakeLists.txt")
  message(FATAL_ERROR "The assimp submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/glfw/CMakeLists.txt")
  message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/glm/CMakeLists.txt")
  message(FATAL_ERROR "The glm submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/hwinfo/CMakeLists.txt")
  message(FATAL_ERROR "The hwinfo submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/jsoncpp/CMakeLists.txt")
  message(FATAL_ERROR "The jsoncpp submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/libsndfile/CMakeLists.txt")
  message(FATAL_ERROR "The libsndfile submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/Lua/CMakeLists.txt")
  message(FATAL_ERROR "The Lua submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/openal-soft/CMakeLists.txt")
  message(FATAL_ERROR "The openal-soft submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()



# Libraries
add_subdirectory(libs/glfw)
#add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)
add_subdirectory(libs/hwinfo)
add_subdirectory(libs/openal-soft)
add_subdirectory(libs/libsndfile)
add_subdirectory(libs/Lua)
add_subdirectory(libs/jsoncpp)
