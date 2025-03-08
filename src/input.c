#include "input.h"
#include "position.h"
#include "render.h"

ECS_COMPONENT_DECLARE(Position);

void InputModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, InputModule);

  ECS_SYSTEM(world, InitInputSystem, EcsOnStart);
}

void InitInputSystem(ecs_iter_t *it) {
  ecs_entity_t input_text = ecs_new(it->world);
  ecs_set(it->world, input_text, Position, {640, 360});
  ecs_set(it->world, input_text, TextRenderer,
          {"Hello", 64, {245, 245, 245, 100}});
}
