#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>

ArrayList *arraylist_create(size_t capacity) {
    ArrayList *list = malloc(sizeof(ArrayList));
    if (!list) return NULL;
    list->size = 0;
    list->capacity = capacity > 0 ? capacity : 10;
    list->items = malloc(sizeof(void*) * list->capacity);
    return list;
}

void arraylist_add(ArrayList *list, void *item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(void*) * list->capacity);
    }
    list->items[list->size++] = item;
}

void *arraylist_get(ArrayList *list, size_t index) {
    if (index >= list->size) return NULL;
    return list->items[index];
}

void arraylist_free(ArrayList *list) {
    if (!list) return;
    free(list->items);
    free(list);
}
