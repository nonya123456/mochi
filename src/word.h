#ifndef WORD_H
#define WORD_H

#include "render.h"
#include <flecs.h>

extern ECS_TAG_DECLARE(Word);

void WordModuleImport(ecs_world_t *world);

void SpawnWordSystem(ecs_iter_t *it);

#endif // WORD_H
