#ifndef RENDER_H
#define RENDER_H

#include <flecs.h>
#include <raylib.h>

#define MAX_CHARS 20

extern ECS_COMPONENT_DECLARE(TextRenderer);

typedef struct {
	char text[MAX_CHARS + 1];
	int font_size;
	Color color;
} TextRenderer;

void RenderModuleImport(ecs_world_t *world);

void RenderSystem(ecs_iter_t *it);

#endif // RENDER_H
