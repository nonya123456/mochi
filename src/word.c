#include "word.h"
#include "input.h"
#include "position.h"
#include "render.h"

ECS_TAG_DECLARE(Word);

void WordModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, WordModule);

  ECS_TAG_DEFINE(world, Word);

  ECS_SYSTEM(world, SpawnWordSystem, EcsOnStart);
  ECS_SYSTEM(world, WordMatchingSystem, EcsOnUpdate);
}

void SpawnWordSystem(ecs_iter_t *it) {
  ecs_entity_t word1 = ecs_new(it->world);
  ecs_set(it->world, word1, Position, {320, -100});
  ecs_set(it->world, word1, Velocity, {0, 40});
  ecs_set(it->world, word1, TextRenderer,
          {ecs_os_strdup("MONKEY"), 48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word1, Word);
}

void WordMatchingSystem(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  ecs_query_t *q = ecs_query(world, {
                                        .terms = {{ecs_id(InputWord)}},
                                    });

  ecs_iter_t input_it = ecs_query_iter(world, q);
  while (ecs_query_next(&input_it)) {
    InputWord *iw = ecs_field(&input_it, InputWord, 0);
    for (int i = 0; i < input_it.count; i++) {
      ecs_query_t *q_word = ecs_query(world, {
                                                 .terms =
                                                     {
                                                         {ecs_id(TextRenderer)},
                                                         {Word},
                                                     },
                                             });

      ecs_iter_t word_it = ecs_query_iter(world, q_word);
      while (ecs_query_next(&word_it)) {
        TextRenderer *t = ecs_field(&word_it, TextRenderer, 0);
        for (int j = 0; j < word_it.count; j++) {
          if (strcmp(t[j].text, iw[i].text) == 0) {
            ecs_os_free(t[j].text);
            ecs_delete(world, word_it.entities[j]);
          }
        }
      }

      ecs_query_fini(q_word);

      ecs_os_free(iw[i].text);
      ecs_delete(world, input_it.entities[i]);
    }
  }

  ecs_query_fini(q);
}
