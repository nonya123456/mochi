#include "window.h"
#include <raylib.h>

void WindowModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, WindowModule);

  ECS_SYSTEM(world, InitWindowSystem, EcsOnStart);
  ECS_SYSTEM(world, CloseWindowSystem, EcsPostFrame);
}

void InitWindowSystem(ecs_iter_t *it) { InitWindow(1280, 720, "App"); }

void CloseWindowSystem(ecs_iter_t *it) {
  if (!WindowShouldClose()) {
    return;
  }

  CloseWindow();
  ecs_quit(it->world);
}
