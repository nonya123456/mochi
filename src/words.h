#ifndef WORDS_H
#define WORDS_H

#include <flecs.h>

extern ECS_COMPONENT_DECLARE(WordList);

typedef struct {
  char **word_list;
  int word_count;
} WordList;

void WordsModuleImport(ecs_world_t *world);

#endif // WORDS_H
