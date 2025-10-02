#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>

typedef struct {
    void **items;    
    size_t size;     
    size_t capacity; 
} ArrayList;


ArrayList *arraylist_create(size_t capacity);


void arraylist_add(ArrayList *list, void *item);


void *arraylist_get(ArrayList *list, size_t index);


void arraylist_free(ArrayList *list);

#endif
