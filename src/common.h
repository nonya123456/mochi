#ifndef COMMON_H
#define COMMON_H

#include <flecs.h>

extern ECS_TAG_DECLARE(EnemyWord);
extern ECS_TAG_DECLARE(PlayerWord);
extern ECS_COMPONENT_DECLARE(String);

typedef ecs_string_t String;

void CommonModuleImport(ecs_world_t *world);

#endif // COMMON_H
