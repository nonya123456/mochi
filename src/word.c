#include "word.h"
#include "position.h"

ECS_TAG_DECLARE(Word);

void WordModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, WordModule);

  ECS_TAG_DEFINE(world, Word);

  ECS_SYSTEM(world, SpawnWordSystem, EcsOnStart);
}

void SpawnWordSystem(ecs_iter_t *it) {
  ecs_entity_t word1 = ecs_new(it->world);
  ecs_set(it->world, word1, Position, {320, -100});
  ecs_set(it->world, word1, Velocity, {0, 40});
  ecs_set(it->world, word1, TextRenderer,
          {"MONKEY\0", 48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word1, Word);
}
