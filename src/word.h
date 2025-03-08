#ifndef WORD_H
#define WORD_H

#include "render.h"
#include <flecs.h>

extern ECS_TAG_DECLARE(EnemyWord);
extern ECS_TAG_DECLARE(PlayerWord);
extern ECS_COMPONENT_DECLARE(String);

typedef ecs_string_t String;

void WordModuleImport(ecs_world_t *world);

void SpawnWordSystem(ecs_iter_t *it);
void WordMatchingSystem(ecs_iter_t *it);

#endif // WORD_H
