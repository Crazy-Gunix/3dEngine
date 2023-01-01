# Copyright 2023 Jacob Gibson
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

add_executable(3dEngine
  main.cpp

  # Audio
  audio/sound_device.cpp
  audio/sound_buffer.cpp
  audio/sound_source.cpp
  audio/music_buffer.cpp

  # Graphics
  graphics/shader.cpp
  graphics/camera.cpp
  graphics/mesh.cpp
  graphics/model.cpp

  ## Menus
  menus/cheat_menu.cpp
  menus/debug_menu.cpp
  menus/help_menu.cpp
  menus/pause_menu.cpp

  # Misc
  misc/clear.cpp
  misc/error_exit.cpp

  # Scripting
  scripting/lua_script_handler.cpp
  scripting/lua_bind_functions.cpp

  # Utils
  utils/load_assets.cpp
  utils/loading_screen.cpp
  utils/object_manager.cpp
  utils/play_audio.cpp
)

add_library(glad STATIC glad.c)
add_library(stb_image STATIC stb_image.cpp)
add_library(imgui STATIC
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp

  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp
)

target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/glfw/include)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/Lua)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/jsoncpp/include)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/glm)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/hwinfo/include)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/openal-soft/include)
target_include_directories(3dEngine PUBLIC ${CMAKE_SOURCE_DIR}/libs/libsndfile/include)
target_include_directories(3dEngine PUBLIC ${CMAKE_BINARY_DIR}/config)

target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(stb_image PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/libs/imgui)
target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/libs/imgui/backends)
target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/libs/glfw/include)

target_link_libraries(3dEngine
  glfw
  glad
  stb_image
  assimp
  imgui
  HWinfo
  OpenAL
  sndfile
  lua_static
  jsoncpp_static

  ${GLFW_LIBRARIES}
)