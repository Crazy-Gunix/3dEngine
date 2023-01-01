/*
Copyright (C) 2023 Jacob Gibson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <thread>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>

#include <audio/sound_device.h>
#include <graphics/camera.h>
#include <graphics/model.h>
#include <menus/cheat_menu.h>
#include <menus/debug_menu.h>
#include <menus/help_menu.h>
#include <menus/pause_menu.h>
#include <misc/clear.h>
#include <misc/error_exit.h>
#include <scripting/lua_script_handler.h>
#include <utils/play_audio.h>
#include <utils/load_assets.h>
#include <utils/loading_screen.h>
#include <utils/object_manager.h>
#include <version.h>

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

bool debug_mode, wireframe_mode = false;
bool pause_menu_active, cheat_menu_active, help_menu_active = false;

bool loading_ready, loading_finished = false;

GLFWimage images[1];
Model models[6];
Model square_model;
std::string path;

// Camera
Camera camera(glm::vec3(0.0f, 0.25f, 3.0f));
float last_x = SCR_WIDTH / 2.0f;
float last_y = SCR_WIDTH / 2.0f;
bool first_mouse = true;

// Delta
float delta_time, last_frame = 0.0f;



void FramebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
void MouseCallback(GLFWwindow* pWindow, double x_pos_in, double y_pos_in);
void KeyCallback(GLFWwindow* pWindow, int key, int scancode,
                                      int action, int mods);
void ProcessInput(GLFWwindow* pWindow);
void UpdateDelta();
void DrawPauseMenu(GLFWwindow* pWindow, ObjectManager* pObjectManager,
                   ImGuiIO& imgui_io, PauseMenu& pause_menu,
                   CheatMenu& cheat_menu);
void DrawDebugMenu(GLFWwindow* pWindow, DebugMenu& debug_menu);
void DrawHelpMenu(GLFWwindow* pWindow, ImGuiIO& imgui_io, HelpMenu& help_menu);
void DrawModels(GLFWwindow* pWindow, ObjectManager* pObjectManager, Shader& model_shader);
void ConfigImGui(GLFWwindow* pWindow, ImGuiIO& imgui_io);



int main(int argc, char** argv) {
  std::cout << "3D Engine Version " << ENGINE_VERSION_MAJOR << '.' 
                                    << ENGINE_VERSION_MINOR << '.' 
                                    << ENGINE_VERSION_PATCH << ' ' 
                                    << ENGINE_VERSION_PHASE << '\n';
  std::cout << "-------------------------\n";

  path=(argc==1) ? "." : argv[1];

  if (!glfwInit()) return EXIT_FAILURE;

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow*pWindow=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, 
                                      "3D Engine", NULL, NULL);
  if (pWindow==NULL) ErrorExit("Failed to create GLFW window.");

  const GLFWvidmode* pMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(pWindow,(int)(pMode->width / 2) - (int)(SCR_WIDTH / 2),
                  (int)(pMode->height / 2) - (int)(SCR_HEIGHT / 2));

  images[0].pixels = stbi_load(
    (path + "/assets/textures/awesomeface.png").c_str(),
    &images[0].width, &images[0].height, 0, 4
  );

  glfwMakeContextCurrent(pWindow);
  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(pWindow, FramebufferSizeCallback);
  glfwSetKeyCallback(pWindow, KeyCallback);
  glfwSetCursorPosCallback(pWindow, MouseCallback);
  // glfwSetScrollCallback(pWindow, ScrollCallback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    ErrorExit("Failed to initialize GLAD.");

  IMGUI_CHECKVERSION(); ImGui::CreateContext();
  ImGuiIO& imgui_io = ImGui::GetIO(); (void)imgui_io;
  ConfigImGui(pWindow, imgui_io);

  SoundDevice* pSoundDevice = SoundDevice::get();

  std::cout << "-------------------------\n"
            << "Loading assets...\n"
            << "-------------------------\n";
  Shader model_shader((path + "/shaders/model.vs").c_str(),
                      (path + "/shaders/model.fs").c_str());
  std::thread loading_thread(LoadModels,
                             std::ref(pWindow), std::ref(models),
                             std::ref(square_model), std::ref(loading_ready),
                             std::ref(loading_finished), path
  );
  LoadingScreen loading_screen(pWindow, path);
  loading_screen.Render(images, imgui_io, loading_ready, loading_finished,
                        SCR_WIDTH, SCR_HEIGHT, "Loading...");
  loading_thread.join();
  glfwMakeContextCurrent(pWindow);
  loading_screen.Render(images, imgui_io, loading_ready, loading_finished,
                        SCR_WIDTH, SCR_HEIGHT, "Loading Complete.");
  std::cout << "-------------------------\n"
            << "Loading complete.\n";

  ObjectManager* pObjectManager = new ObjectManager();

  CheatMenu cheat_menu;
  DebugMenu debug_menu(pWindow);
  glfwMakeContextCurrent(pWindow);
  HelpMenu help_menu;
  PauseMenu pause_menu;

  LuaScriptHandler lua_script_handler(pObjectManager);
  lua_script_handler.AddScript("scripts/hello.lua");

  glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  PlayMusic(path + "/assets/sounds/music/music.ogg", true);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE); glCullFace(GL_BACK);  glFrontFace(GL_CCW);
  while (!glfwWindowShouldClose(pWindow)) {
    if (pause_menu_active) { // Pause Menu
      DrawPauseMenu(pWindow, pObjectManager, imgui_io, pause_menu, cheat_menu);
      continue;
    } else if (help_menu_active) {
      DrawHelpMenu(pWindow, imgui_io, help_menu);
      continue;
    } // Game

    glPolygonMode(GL_FRONT_AND_BACK, ((!wireframe_mode) ? GL_FILL : GL_LINE));
    glfwSetWindowIcon(pWindow, 1, images);

    UpdateDelta();
    ProcessInput(pWindow);

    ClearScreen(0.5f, 0.8f, 0.9f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DrawModels(pWindow, pObjectManager, model_shader);

    if (debug_mode)
      DrawDebugMenu(pWindow, debug_menu);
    if (cheat_menu_active)
      cheat_menu.Render(pWindow, camera, pObjectManager,
                        cheat_menu_active, pause_menu_active);

    lua_script_handler.RunUpdateFuncs(delta_time);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* pBackupCurrentContext = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(pBackupCurrentContext);
    }

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  delete pObjectManager;
  stbi_image_free(images[0].pixels);

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return EXIT_SUCCESS;
}



void FramebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
  glViewport(0, 0, width, height);
}
void MouseCallback(GLFWwindow* pWindow, double x_pos_in, double y_pos_in) {
  float x_pos = static_cast<float>(x_pos_in);
  float y_pos = static_cast<float>(y_pos_in);

  if (first_mouse) {
    last_x = x_pos;
    last_y = y_pos;
    first_mouse = false;
  }

  float x_offset = x_pos - last_x;
  float y_offset = last_y - y_pos; 
  last_x = x_pos;
  last_y = y_pos;

  camera.ProcessMouseMovement(x_offset, y_offset);
}
void KeyCallback(GLFWwindow* pWindow, int key, int scancode,
                                      int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    pause_menu_active = !pause_menu_active;
    glfwSetInputMode(pWindow, GLFW_CURSOR, 
                    ((pause_menu_active) ? GLFW_CURSOR_NORMAL
                                         : GLFW_CURSOR_DISABLED));
  }

  if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
    PlaySound(path + "/assets/sounds/random/untitled.ogg");

  if (key == GLFW_KEY_F5 && action == GLFW_PRESS && pause_menu_active)
    cheat_menu_active=!cheat_menu_active;

  if (key == GLFW_KEY_F1 && action == GLFW_PRESS && !pause_menu_active)
    help_menu_active=true;
  if (key == GLFW_KEY_F3 && action == GLFW_PRESS && !pause_menu_active)
    debug_mode=!debug_mode;
  if (key == GLFW_KEY_F8 && action == GLFW_PRESS && !pause_menu_active)
    wireframe_mode=!wireframe_mode;
}

void ProcessInput(GLFWwindow* pWindow) {

  bool zoom =glfwGetKey(pWindow, GLFW_KEY_C);

  camera.zoom_ = (zoom) ? 30 : kZoom;

  bool speed_boost=(glfwGetKey(pWindow, GLFW_KEY_R) && !zoom);

  if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(kForward, speed_boost, delta_time);
  if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(kBackward, speed_boost, delta_time);
  if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(kLeft, speed_boost, delta_time);
  if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(kRight, speed_boost, delta_time);
}
void UpdateDelta() {
  float current_frame = static_cast<float>(glfwGetTime());
  delta_time = current_frame - last_frame;
  last_frame = current_frame;
}

void DrawPauseMenu(GLFWwindow* pWindow, ObjectManager* pObjectManager,
                   ImGuiIO& imgui_io, PauseMenu& pause_menu, 
                   CheatMenu& cheat_menu) {
  UpdateDelta();
  ClearScreen(0.1f, 0.15f, 0.15f);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  pause_menu.Render(pWindow, pause_menu_active, SCR_WIDTH, SCR_HEIGHT);

  if (cheat_menu_active)
    cheat_menu.Render(pWindow, camera, pObjectManager,
                      cheat_menu_active, pause_menu_active);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* pBackupCurrentContext = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(pBackupCurrentContext);
  }
  glfwSetWindowIcon(pWindow, 1, images);

  glfwSwapBuffers(pWindow);
  glfwPollEvents();
}
void DrawDebugMenu(GLFWwindow* pWindow, DebugMenu& debug_menu) {
  int window_x, window_y;
  glfwGetWindowPos(pWindow, &window_x, &window_y);

  unsigned int fps = round(1 / delta_time);
  glm::vec3 pos = camera.position_;
  glm::vec2 text_pos = glm::vec2((float)window_x, (float)window_y);

  debug_menu.Render(text_pos, pos, fps);
}
void DrawHelpMenu(GLFWwindow* pWindow, ImGuiIO& imgui_io, HelpMenu& help_menu) {
  UpdateDelta();
  ClearScreen(0.0f, 0.0f, 0.0f);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  help_menu.Render(pWindow, help_menu_active, SCR_WIDTH, SCR_HEIGHT);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* pBackupCurrentContext = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(pBackupCurrentContext);
  }

  glfwSwapBuffers(pWindow);
  glfwPollEvents();
}
void DrawModels(GLFWwindow* pWindow, ObjectManager* pObjectManager, Shader& model_shader) {
  static float rot = 0.0f;
  model_shader.Use();

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(camera.zoom_),
                                (float)SCR_WIDTH / (float)SCR_HEIGHT,
                                0.1f, 100.0f);
  view = camera.GetViewMatrix();
  model_shader.set_mat_4("projection", projection);
  model_shader.set_mat_4("view", view);

  glm::mat4 model;

  for(Object i : pObjectManager->get_objects()){
    model = glm::mat4(1.0f);
    model = glm::translate(model, i.position);
    if (i.type == kObjectTypeBanana) {
      model = glm::rotate(model, -rot, glm::vec3(0.0f, 1.0f, 0.0f));
    } else {
      model = glm::rotate(model, i.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, i.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, i.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    }
    model = glm::scale(model, i.scale);
    model_shader.set_mat_4("model", model);
    models[(int)i.type].Draw(model_shader);
  }

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
  model_shader.set_mat_4("model", model);
  square_model.Draw(model_shader);

  rot = (rot < 360) ? rot + 0.01f : rot = 0;
}

void ConfigImGui(GLFWwindow* pWindow, ImGuiIO& imgui_io) {
  imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  imgui_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  imgui_io.IniFilename = NULL;
  ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
  ImGui_ImplOpenGL3_Init("#version 330");
  ImGui::StyleColorsDark();
  ImGuiStyle& imgui_style = ImGui::GetStyle();
  if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    imgui_style.WindowRounding = 0.0f;
    imgui_style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
}