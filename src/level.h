#ifndef LEVEL_H
#define LEVEL_H

#include <flecs.h>

extern ECS_COMPONENT_DECLARE(Score);
extern ECS_COMPONENT_DECLARE(SpawnTimer);

typedef int Score;

typedef struct {
  float elapsed;
  float duration;
} SpawnTimer;

void LevelModuleImport(ecs_world_t *world);

void SpawnWordSystem(ecs_iter_t *it);
void WordMatchingSystem(ecs_iter_t *it);
void ResetScoreSystem(ecs_iter_t *it);

#endif // LEVEL_H
