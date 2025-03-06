#include "render.h"
#include "window.h"
#include <flecs.h>
#include <raylib.h>

int main() {
  ecs_world_t *world = ecs_init();

  ECS_IMPORT(world, WindowModule);
  ECS_IMPORT(world, RenderModule);

  while (ecs_progress(world, 0)) {
  }

  return ecs_fini(world);
}
