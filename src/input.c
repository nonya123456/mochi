#include "input.h"
#include "position.h"
#include "raylib.h"
#include "render.h"
#include <stdlib.h>

ECS_COMPONENT_DECLARE(InputText);
ECS_COMPONENT_DECLARE(InputWord);

void InputModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, InputModule);

  ECS_COMPONENT_DEFINE(world, InputText);
  ECS_COMPONENT_DEFINE(world, InputWord);

  ECS_SYSTEM(world, InitInputSystem, EcsOnStart);
  ECS_SYSTEM(world, UpdateInputTextSystem, EcsOnUpdate,
             render.module.TextRenderer, InputText);
}

void InitInputSystem(ecs_iter_t *it) {
  char *text = malloc(MAX_INPUT_CHARS + 1);
  ecs_entity_t input_text = ecs_new(it->world);
  ecs_set(it->world, input_text, Position, {640, 360});
  ecs_set(it->world, input_text, TextRenderer,
          {text, 64, {245, 245, 245, 100}});
  ecs_set(it->world, input_text, InputText, {0});
}

void UpdateInputTextSystem(ecs_iter_t *it) {
  TextRenderer *t = ecs_field(it, TextRenderer, 0);
  InputText *i = ecs_field(it, InputText, 1);

  int key = GetCharPressed();

  if ((key >= 65) && (key <= 90) && (i[0].count < MAX_INPUT_CHARS)) {
    t[0].text[i[0].count] = (char)key;
    t[0].text[i[0].count + 1] = '\0';
    i[0].count++;
    return;
  }

  if ((key >= 97) && (key <= 122) && (i[0].count < MAX_INPUT_CHARS)) {
    t[0].text[i[0].count] = (char)(key - 32);
    t[0].text[i[0].count + 1] = '\0';
    i[0].count++;
    return;
  }

  if (IsKeyPressed(KEY_BACKSPACE)) {
    i[0].count--;
    if (i[0].count < 0) {
      i[0].count = 0;
    }
    t[0].text[i[0].count] = '\0';
    return;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    ecs_string_t text = malloc(MAX_INPUT_CHARS + 1);
    strcpy(text, t[0].text);
    ecs_entity_t input_word = ecs_new(it->world);
    ecs_set(it->world, input_word, InputWord, {text});
    i[0].count = 0;
    t[0].text[i[0].count] = '\0';
    return;
  }
}
