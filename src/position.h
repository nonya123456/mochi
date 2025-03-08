#ifndef POSITION_H
#define POSITION_H

#include <flecs.h>
#include <raylib.h>

extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Velocity);

typedef Vector2 Position;
typedef Vector2 Velocity;

void PositionModuleImport(ecs_world_t *world);

void MoveSystem(ecs_iter_t *it);

#endif // POSITION_H
