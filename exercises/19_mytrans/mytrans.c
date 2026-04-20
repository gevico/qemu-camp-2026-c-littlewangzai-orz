// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    // TODO: 在这里添加你的代码
    str[strcspn(str, "\n")] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    // TODO: 在这里添加你的代码
  while( fgets(current_word, 100, file) != NULL) {
      trim(current_word);
      char *word = current_word + 1; 
      if(fgets(current_translation, 1024, file) == NULL) {
        return -1;
      }
      else {
        trim(current_translation);
        char *trans = current_translation + 6;
        if(!hash_table_insert(table, word, trans)) {
            return -1;
        }
      }
      *dict_count = *dict_count + 1 ;
  }
  fclose(file);
  return 0;
}
