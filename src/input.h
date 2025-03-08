#ifndef INPUT_H
#define INPUT_H

#include <flecs.h>

#define MAX_INPUT_CHARS 20

extern ECS_COMPONENT_DECLARE(InputText);
extern ECS_COMPONENT_DECLARE(InputWord);

typedef struct {
	int count;
} InputText;

typedef struct {
	char* text;
} InputWord;

void InputModuleImport(ecs_world_t *world);

void InitInputSystem(ecs_iter_t *it);
void UpdateInputTextSystem(ecs_iter_t *it);

#endif // INPUT_H
