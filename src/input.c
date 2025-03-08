#include "input.h"
#include "position.h"
#include "raylib.h"
#include "render.h"
#include "word.h"
#include <stdlib.h>

ECS_COMPONENT_DECLARE(InputText);

void InputModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, InputModule);

  ECS_COMPONENT_DEFINE(world, InputText);

  ECS_SYSTEM(world, InitInputSystem, EcsOnStart);
  ECS_SYSTEM(world, UpdateInputTextSystem, EcsOnUpdate, word.module.String,
             InputText);
}

void InitInputSystem(ecs_iter_t *it) {
  ecs_entity_t input_text = ecs_new(it->world);
  ecs_set(it->world, input_text, String, {ecs_os_malloc(20)});
  ecs_set(it->world, input_text, Position, {640, 360});
  ecs_set(it->world, input_text, TextRenderer, {64, {245, 245, 245, 100}});
  ecs_set(it->world, input_text, InputText, {0});
}

void UpdateInputTextSystem(ecs_iter_t *it) {
  String *s = ecs_field(it, String, 0);
  InputText *i = ecs_field(it, InputText, 1);

  int key = GetCharPressed();

  if ((key >= 65) && (key <= 90) && (i[0].count < MAX_INPUT_CHARS)) {
    s[0][i[0].count] = (char)key;
    s[0][i[0].count + 1] = '\0';
    i[0].count++;
    return;
  }

  if ((key >= 97) && (key <= 122) && (i[0].count < MAX_INPUT_CHARS)) {
    s[0][i[0].count] = (char)(key - 32);
    s[0][i[0].count + 1] = '\0';
    i[0].count++;
    return;
  }

  if (IsKeyPressed(KEY_BACKSPACE)) {
    i[0].count--;
    if (i[0].count < 0) {
      i[0].count = 0;
    }
    s[0][i[0].count] = '\0';
    return;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    ecs_entity_t player_word = ecs_new(it->world);
    ecs_set(it->world, player_word, String, {ecs_os_strdup(s[0])});
    ecs_add_id(it->world, player_word, PlayerWord);
    i[0].count = 0;
    s[0][i[0].count] = '\0';
    return;
  }
}
