#include "level.h"
#include "common.h"
#include "position.h"
#include "render.h"

ECS_COMPONENT_DECLARE(Score);

void LevelModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, LevelModule);

  ECS_COMPONENT_DEFINE(world, Score);
  ecs_singleton_set(world, Score, {0});

  ECS_SYSTEM(world, SpawnWordSystem, EcsOnStart);
  ECS_SYSTEM(world, WordMatchingSystem, EcsOnUpdate);
  ECS_SYSTEM(world, ResetScoreSystem, EcsOnUpdate);
}

void SpawnWordSystem(ecs_iter_t *it) {
  ecs_entity_t word1 = ecs_new(it->world);
  ecs_set(it->world, word1, String, {ecs_os_strdup("MONKEY")});
  ecs_set(it->world, word1, Position, {320, -100});
  ecs_set(it->world, word1, Velocity, {0, 40});
  ecs_set(it->world, word1, TextRenderer, {48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word1, EnemyWord);

  ecs_entity_t word2 = ecs_new(it->world);
  ecs_set(it->world, word2, String, {ecs_os_strdup("APPLE")});
  ecs_set(it->world, word2, Position, {640, -100});
  ecs_set(it->world, word2, Velocity, {0, 60});
  ecs_set(it->world, word2, TextRenderer, {48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word2, EnemyWord);

  ecs_entity_t word3 = ecs_new(it->world);
  ecs_set(it->world, word3, String, {ecs_os_strdup("MONKEY")});
  ecs_set(it->world, word3, Position, {960, -100});
  ecs_set(it->world, word3, Velocity, {0, 70});
  ecs_set(it->world, word3, TextRenderer, {48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word3, EnemyWord);
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

      ecs_os_free(s[i]);
      ecs_delete(world, eit.entities[i]);
      ecs_singleton_set(world, Score, {0});
    }
  }
}
