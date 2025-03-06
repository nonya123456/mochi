#ifndef WINDOW_H
#define WINDOW_H

#include <flecs.h>

void WindowModuleImport(ecs_world_t *world);

void InitWindowSystem(ecs_iter_t *it);
void CloseWindowSystem(ecs_iter_t *it);

#endif // WINDOW_H
