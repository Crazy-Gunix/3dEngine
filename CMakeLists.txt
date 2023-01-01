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

# Libraries
add_subdirectory(libs/glfw)
#add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)
add_subdirectory(libs/hwinfo)
add_subdirectory(libs/openal-soft)
add_subdirectory(libs/libsndfile)
add_subdirectory(libs/Lua)
add_subdirectory(libs/jsoncpp)