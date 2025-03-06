#ifndef RENDER_H
#define RENDER_H

#include <flecs.h>

void RenderModuleImport(ecs_world_t *world);

void RenderSystem(ecs_iter_t *it);

#endif // RENDER_H
