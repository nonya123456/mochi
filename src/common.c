#include "common.h"

ECS_TAG_DECLARE(EnemyWord);
ECS_TAG_DECLARE(PlayerWord);
ECS_COMPONENT_DECLARE(String);

void CommonModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, CommonModule);

  ECS_TAG_DEFINE(world, EnemyWord);
  ECS_TAG_DEFINE(world, PlayerWord);
  ECS_COMPONENT_DEFINE(world, String);
}
