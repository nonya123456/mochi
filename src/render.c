#include "render.h"
#include "common.h"
#include "position.h"

ECS_COMPONENT_DECLARE(TextRenderer);

void RenderModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, RenderModule);

  ECS_COMPONENT_DEFINE(world, TextRenderer);

  ECS_SYSTEM(world, RenderSystem, EcsOnUpdate);
}

void RenderSystem(ecs_iter_t *it) {
  BeginDrawing();

  Color c = {54, 57, 62, 255};
  ClearBackground(c);
  DrawFPS(0, 0);

  ecs_world_t *world = it->world;
  ecs_query_t *q = ecs_query(world, {
                                        .terms =
                                            {
                                                {ecs_id(Position)},
                                                {ecs_id(TextRenderer)},
                                                {ecs_id(String)},
                                            },
                                    });

  ecs_iter_t text_it = ecs_query_iter(world, q);
  while (ecs_query_next(&text_it)) {
    Position *p = ecs_field(&text_it, Position, 0);
    TextRenderer *t = ecs_field(&text_it, TextRenderer, 1);
    String *s = ecs_field(&text_it, String, 2);

    for (int i = 0; i < text_it.count; i++) {
      int text_width = MeasureText(s[i], t[i].font_size);
      int text_x = p[i].x - text_width / 2.;
      int text_y = p[i].y - t[i].font_size / 2.;
      DrawText(s[i], text_x, text_y, t[i].font_size, t[i].color);
    }
  }
  ecs_query_fini(q);

  EndDrawing();
}
