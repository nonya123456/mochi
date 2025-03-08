#include "position.h"
#include "raylib.h"

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Velocity);

void PositionModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, PositionModule);

  ECS_COMPONENT_DEFINE(world, Position);
  ECS_COMPONENT_DEFINE(world, Velocity);

  ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, Position, Velocity);
}

void MoveSystem(ecs_iter_t *it) {
  Position *p = ecs_field(it, Position, 0);
  Velocity *v = ecs_field(it, Velocity, 1);

  for (int i = 0; i < it->count; i++) {
    p[i].x += v[i].x * GetFrameTime();
    p[i].y += v[i].y * GetFrameTime();
  }
}
