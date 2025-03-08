#include "words.h"
#include "cJSON.h"
#include "raylib.h"
#include <ctype.h>
#include <stdlib.h>

ECS_COMPONENT_DECLARE(WordList);

void WordsModuleImport(ecs_world_t *world) {
  ECS_MODULE(world, WordsModule);

  const char *json_file_path = "res/words.json";
  char *json_data = LoadFileText(json_file_path);
  if (json_data == NULL) {
    TraceLog(LOG_FATAL, "Failed to load words.json");
    return;
  }

  cJSON *json = cJSON_Parse(json_data);
  cJSON *words_array = cJSON_GetObjectItem(json, "words");
  int word_count = cJSON_GetArraySize(words_array);
  char **word_list = malloc(sizeof(char *) * word_count);

  for (int i = 0; i < word_count; i++) {
    cJSON *item = cJSON_GetArrayItem(words_array, i);
    word_list[i] = strdup(item->valuestring);

    char *s = word_list[i];
    while (*s) {
      *s = toupper((unsigned char)*s);
      s++;
    }
  }

  cJSON_Delete(json);
  UnloadFileText(json_data);

  ECS_COMPONENT_DEFINE(world, WordList);
  ecs_singleton_set(world, WordList, {word_list, word_count});
}
