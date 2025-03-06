#include "render.h"
#include "raylib.h"

void RenderModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, RenderModule);

  ECS_SYSTEM(world, RenderSystem, EcsOnUpdate);
}

void RenderSystem(ecs_iter_t *it) {
  BeginDrawing();
  Color c = {54, 57, 62, 255};
  ClearBackground(c);
  EndDrawing();
}
