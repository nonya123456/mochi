#ifndef RENDER_H
#define RENDER_H

#include <flecs.h>
#include <raylib.h>

extern ECS_COMPONENT_DECLARE(TextRenderer);

typedef struct {
	char *text;
	int font_size;
	Color color;
} TextRenderer;

void RenderModuleImport(ecs_world_t *world);

void RenderSystem(ecs_iter_t *it);

#endif // RENDER_H
