#include "level.h"
#include "common.h"
#include "position.h"
#include "render.h"

void LevelModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, LevelModule);

  ECS_SYSTEM(world, SpawnWordSystem, EcsOnStart);
  ECS_SYSTEM(world, WordMatchingSystem, EcsOnUpdate);
}

void SpawnWordSystem(ecs_iter_t *it) {
  ecs_entity_t word1 = ecs_new(it->world);
  ecs_set(it->world, word1, String, {ecs_os_strdup("MONKEY")});
  ecs_set(it->world, word1, Position, {320, -100});
  ecs_set(it->world, word1, Velocity, {0, 40});
  ecs_set(it->world, word1, TextRenderer, {48, {245, 245, 245, 255}});
  ecs_add_id(it->world, word1, EnemyWord);
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
            ecs_os_free(es[j]);
            ecs_delete(world, eit.entities[j]);
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
