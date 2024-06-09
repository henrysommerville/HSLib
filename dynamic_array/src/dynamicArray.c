#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void *items;
  size_t length;
  size_t capacity;
  size_t itemSize;
} DA_struct;

DA_struct dynamic_array_init(size_t itemSize, size_t capacity) {
  DA_struct array = {0};
  array.capacity = capacity;
  array.itemSize = itemSize;
  if (capacity * itemSize > 0) {
    array.items = malloc(itemSize * capacity);
  } else {
    array.items = NULL;
  }
  return array;
}

size_t dynamic_array_append(DA_struct *array, void *item) {
  int *location = NULL;
  if (array->items == NULL) {
    array->items = malloc(array->itemSize);

    if (array->items == NULL) {
      printf("Error: In dynamic_array_append - malloc() Failed.\n");
      return false;
    }

    array->length = 1;
    array->capacity = 1;
  } else if (array->capacity <= array->length) {
    size_t new_capacity = array->capacity * 2;
    array->items = realloc(array->items, new_capacity);
    if (array->items == NULL) {
      printf("ERROR: In dynamic_array_append - realloc() failed\n");
      return false;
    }

    array->capacity = new_capacity;
  }

  location = (int *)(array->items) + (array->itemSize * array->length);

  if (memcpy(location, item, array->itemSize) == NULL) {
    printf("ERROR: In dynamic_array_append - memcpy() failed\n");
    return false;
  }

  array->length++;
  return true;
}

int main() {
  DA_struct array = dynamic_array_init(sizeof(int), 2);

  int here = 3;
  printf("here");
  dynamic_array_append(&array, &here);
  dynamic_array_append(&array, &here);
  dynamic_array_append(&array, &here);

  return 0;
}
