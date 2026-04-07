#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef uint8_t HEAP_PROPERTY;

#define MIN_HEAP 0
#define MAX_HEAP 1

void heap_config(HEAP_PROPERTY prop, int size);
void insert(int* heap, int value);
void delete_root(int* heap);
void naive_heapsort(int* heap, int size);
void heapify(int* heap, int index);
void heapsort(int* heap, int size);

#endif // HEAP_H
