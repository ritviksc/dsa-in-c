/* Heap is a useful data structure for implementing pirority queues. A heap is a tree data structure that follows the heap property.
   The heap property could be the MAX_HEAP property or MIN_HEAP property. For a max heap, the parent node will always have a greater
   value than its possible children, while the latter is the opposite - the parents value will be smaller than its children.
   The most common implementation of a heap is the binary heap, where a node can have upto two children, but k-ary heaps to exits if needed.

   The heap should be filled from top to bottom and left to right. We can implement it using a array or linked list, whatever is favoured.

   Complexity of inserting and removing from a (binary) heap:
   Each layer of a heap can hold up to 2^k elements, starting from layer 0 (root)
   Total elements in a heap can be written as 2^(k+1) + 1 where k is the number of layers in the heap
   So total layers in a heap is log n where n is the number of elements.
   So when we iterate though branch(es) for inserting and remvoing from heap we get complexity O(log n)
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// some typedefs
typedef uint8_t HEAP_TYPE

// what heap type we need
#define MIN_HEAP 0
#define MAX_HEAP 1

HEAP_TYPE heap_type;

int heap_size = 0;
int heap_capacity;
int vacant_index = 0;

// helper function to swap two elements in a array
void swap(int* array, int i, int j){
    if (!array){
        return;
    }
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;

}

// for our sake we will consider nodes to be integers, and return a 'empty' array of n elements with heap type set.
// To actually make heap use make_heap()
int* alloc_heap(HEAP_TYPE type, int size){
    // set heap property
    heap_type = type;

    heap_size = size;
    heap_capacity = size;

    int *heap = calloc(size,sizeof(int));
    if (!heap){
        exit(EXIT_FAILURE);
    }
}

// append items to a heap in a sequential fashion
void add_to_heap(int* heap, int value){
    if (!heap){
        return;
    }

    if (heap_capacity > 0){
        if (vacant_index = 0){
            heap[vacant_index++] = value;
            heap_capacity--;
            return;
        }
        heap[vacant_index] = value;
        int curr = vacant_index;
        if (heap_type = MAX_HEAP){
            while (curr > 0){
                int parent = ((curr) - 1 )/ 2;
                if (heap[curr] > heap[parent]){
                    swap(heap,curr,parent);
                }
                curr = parent;
            }
        }

        if (heap_type = MIN_HEAP){
            while (curr > 0){
                int parent = ((curr) - 1) / 2;
                if (heap[curr] < heap[parent]){
                    swap(heap,curr,parent);
                }
                curr = parent;
            }
        }

        vacant_index++;
        heap_capacity--;
    }
}

int extract_root(int* heap, int value){
    if (!heap){
        return;
    }

    if (heap_capacity > 0){
        int root = heap[0];
        int last_node = heap[vacant_index - 1];
        swap(heap,0,vacant_index - 1);

        if (heap_type == MAX_HEAP){
            int curr = 0;
            while (curr < heap_size) {
                int left_child = 2 * curr + 1;
                int right_child = 2 * curr + 2;
                int largest = curr;

                if (left_child < heap_size && heap[left_child] > heap[largest]) {
                    largest = left_child;
                }

                if (right_child < heap_size && heap[right_child] > heap[largest]) {
                    largest = right_child;
                }

                if (largest != curr) {
                    swap(heap, curr, largest);
                    curr = largest;
                } else {
                    break;
                }
            }
        } else if (heap_type == MIN_HEAP)
    }
}


// Exchange nodes and in subtree to fulfil heap property.
void heapify(int* heap, int i, int heap_size){
    if (i > heap_size || !heap ){
        return;
    }

    int left_child = 2*i + 1;
    int right_child = 2*i + 2;
    
    if (heap_type == MAX_HEAP){
        int largest = i;
        if (left_child < heap_size && heap[left_child] > heap[largest])
            largest = left_child;
        if (right_child < heap_size && heap[right_child] > heap[largest])
            largest = right_child;

        if (largest != i){
            swap(heap, i, largest);
            heapify(heap, largest);
        }
    }
    else if (heap_type == MIN_HEAP){
        int smallest = i;
        if (left_child < heap_size && heap[left_child] < heap[smallest])
            smallest = left_child;
        if (right_child < heap_size && heap[right_child] < heap[smallest])
            smallest = right_child;

        if (smallest != i){
            swap(heap, i, smallest);
            heapify(heap,smallest);
        }
    }
}

  
    void heapsort(int* heap, int size){
        if (!heap){
            return;
        }

        for (int i = size / 2 - 1; i >= 0; i--){
            heapify(heap, i);
        }

        for (int i = size - 1; i > 0; i--){
            swap(heap, 0, i);
            heapify(heap,0,i);
        }
    }

    


