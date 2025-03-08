#include "position.h"

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Velocity);

void PositionModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, PositionModule);

  ECS_COMPONENT_DEFINE(world, Position);
  ECS_COMPONENT_DEFINE(world, Velocity);
}
