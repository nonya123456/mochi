#include "render.h"
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
  ecs_query_t *q = ecs_query(world, {.terms = {
                                         {ecs_id(Position)},
                                         {ecs_id(TextRenderer)},
                                     }});

  ecs_iter_t input_it = ecs_query_iter(world, q);
  while (ecs_query_next(&input_it)) {
    Position *p = ecs_field(&input_it, Position, 0);
    TextRenderer *t = ecs_field(&input_it, TextRenderer, 1);
    for (int i = 0; i < input_it.count; i++) {
      int text_width = MeasureText(t[i].text, t[i].font_size);
      int text_x = p[i].x - text_width / 2.;
      int text_y = p[i].y - t[i].font_size / 2.;
      DrawText(t[i].text, text_x, text_y, t[i].font_size, t[i].color);
    }
  }
  ecs_query_fini(q);

  EndDrawing();
}
