#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct DA_struct {
  void *items;
  size_t length;
  size_t capacity;
  size_t itemSize;
} DA_struct;

DA_struct dynamic_array_init(size_t itemSize, size_t capacity);
int dynamic_array_append(DA_struct *array, void *item);
void *dynamic_array_pop(DA_struct *array);
void *dynamic_array_remove(DA_struct *array, void *item);
void dynamic_array_free(DA_struct *array);
int dynamic_array_index(DA_struct *array, int index);
size_t dynamic_array_length(DA_struct *array);

#endif
