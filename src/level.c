#include "level.h"
#include "common.h"
#include "position.h"
#include "raylib.h"
#include "render.h"
#include "words.h"
#include <raymath.h>

ECS_COMPONENT_DECLARE(Score);
ECS_COMPONENT_DECLARE(SpawnTimer);

void LevelModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, LevelModule);

  ECS_COMPONENT_DEFINE(world, Score);
  ecs_singleton_set(world, Score, {0});

  ECS_COMPONENT_DEFINE(world, SpawnTimer);
  ecs_singleton_set(world, SpawnTimer, {0, 1});

  ECS_SYSTEM(world, SpawnWordSystem, EcsOnUpdate);
  ECS_SYSTEM(world, WordMatchingSystem, EcsOnUpdate);
  ECS_SYSTEM(world, ResetScoreSystem, EcsOnUpdate);
}

void spawn_one_word(ecs_iter_t *it) {
  const WordList *word_list = ecs_singleton_get(it->world, WordList);
  if (word_list == NULL) {
    return;
  }

  ecs_entity_t word = ecs_new(it->world);

  int word_index = GetRandomValue(0, word_list->word_count - 1);
  ecs_set(it->world, word, String,
          {ecs_os_strdup(word_list->word_list[word_index])});

  float position = GetRandomValue(180, 900);
  ecs_set(it->world, word, Position, {position, -48});

  ecs_set(it->world, word, Velocity, {0, 128});
  ecs_set(it->world, word, TextRenderer, {48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word, EnemyWord);
}

void SpawnWordSystem(ecs_iter_t *it) {
  const SpawnTimer *timer = ecs_singleton_get(it->world, SpawnTimer);
  if (timer == NULL) {
    return;
  }

  float new_elapsed = timer->elapsed + GetFrameTime();
  if (new_elapsed > timer->duration) {
    spawn_one_word(it);
    new_elapsed = 0;
  }

  ecs_singleton_set(it->world, SpawnTimer, {new_elapsed, timer->duration});
}

void WordMatchingSystem(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  ecs_query_t *pq = ecs_query(world, {
                                         .terms =
                                             {
                                                 {ecs_id(String)},
                                                 {PlayerWord},
                                             },
                                     });

  ecs_iter_t pit = ecs_query_iter(world, pq);
  while (ecs_query_next(&pit)) {
    String *ps = ecs_field(&pit, String, 0);
    for (int i = 0; i < pit.count; i++) {
      ecs_query_t *eq = ecs_query(world, {
                                             .terms =
                                                 {
                                                     {ecs_id(String)},
                                                     {EnemyWord},
                                                 },
                                         });

      ecs_iter_t eit = ecs_query_iter(world, eq);
      while (ecs_query_next(&eit)) {
        String *es = ecs_field(&eit, String, 0);
        for (int j = 0; j < eit.count; j++) {
          if (strcmp(ps[i], es[j]) == 0) {
            const Score *score = ecs_singleton_get(world, Score);
            if (score != NULL) {
              ecs_singleton_set(world, Score, {*score + 1});
              ecs_os_free(es[j]);
              ecs_delete(world, eit.entities[j]);
            }
          }
        }
      }

      ecs_query_fini(eq);

      ecs_os_free(ps[i]);
      ecs_delete(world, pit.entities[i]);
    }
  }

  ecs_query_fini(pq);
}

void clear_enemy_words(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  ecs_query_t *eq = ecs_query(world, {
                                         .terms =
                                             {
                                                 {ecs_id(String)},
                                                 {EnemyWord},
                                             },

                                     });
  ecs_iter_t eit = ecs_query_iter(world, eq);
  while (ecs_query_next(&eit)) {
    String *s = ecs_field(&eit, String, 0);
    for (int i = 0; i < eit.count; i++) {
      ecs_os_free(s[i]);
      ecs_delete(world, eit.entities[i]);
    }
  }
}

void ResetScoreSystem(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  ecs_query_t *eq = ecs_query(world, {
                                         .terms =
                                             {
                                                 {ecs_id(Position)},
                                                 {ecs_id(String)},
                                                 {EnemyWord},
                                             },
                                     });

  ecs_iter_t eit = ecs_query_iter(world, eq);
  while (ecs_query_next(&eit)) {
    Position *p = ecs_field(&eit, Position, 0);
    String *s = ecs_field(&eit, String, 1);

    for (int i = 0; i < eit.count; i++) {
      if (p[i].y < 720) {
        continue;
      }

      clear_enemy_words(it);
      ecs_singleton_set(world, Score, {0});
    }
  }
}
