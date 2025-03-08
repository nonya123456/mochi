#include "common.h"
#include "input.h"
#include "level.h"
#include "position.h"
#include "render.h"
#include "window.h"
#include <flecs.h>
#include <raylib.h>

int main() {
  ecs_world_t *world = ecs_init();

  ECS_IMPORT(world, CommonModule);
  ECS_IMPORT(world, WindowModule);
  ECS_IMPORT(world, PositionModule);
  ECS_IMPORT(world, RenderModule);
  ECS_IMPORT(world, LevelModule);
  ECS_IMPORT(world, InputModule);

  while (ecs_progress(world, 0)) {
  }

  return ecs_fini(world);
}
