#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../include/dynamicArray.h"

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

int dynamic_array_append(DA_struct *array, void *item) {
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

void *dynamic_array_pop(DA_struct *array) { return NULL; }

void *dynamic_array_remove(DA_struct *array, void *item) {
  int i = 0;
  int *location = (int *)array->items;
  int count = 0;
  size_t remainder = 0;
  
  for (i = 0; i < array->length; ++i) {
    if (memcmp(location, item, array->itemSize) == 0) {
      count = array->capacity - i - 1;
      remainder = count * array->itemSize;

      //copy remainding memory to location.
      if (memmove(location, location + array->itemSize, remainder) == NULL) {
        printf("ERROR: in dynamic_array_remove - memcpy failed");
        fflush(stdout);
        exit(1);
      }
      array->length--;
      /*if (array->length * array->itemSize <= array->capacity / 2) {*/
      /*  size_t new_capacity = array->capacity / 2;*/
      /*  array->items = realloc(array->items, new_capacity * array->itemSize);*/
      /*  array->capacity = new_capacity;*/
      /*}*/
      return NULL;
    }

    location += array->itemSize;
  }
  return NULL;
}

void dynamic_array_free(DA_struct *array) {
  if (array->length > 0) {
      free(array->items);
  }
}

int dynamic_array_index(DA_struct *array, int index) { return 0; }

size_t dynamic_array_length(DA_struct *array) { return 0; }

int main() {
  DA_struct array = dynamic_array_init(sizeof(int), 2);

  int here = 3;
  printf("here\n");
  fflush(stdout);
  dynamic_array_append(&array, &here);
  dynamic_array_append(&array, &here);
  dynamic_array_remove(&array, &here);
  printf("DYNAMIC ARRAY LENGTH: %zu", array.length);
  fflush(stdout);
  dynamic_array_free(&array);
  return 0;
}
