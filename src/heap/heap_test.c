#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(void){
    /*
    int *my_heap = malloc(sizeof(int) * 15);
    heap_config(MAX_HEAP,15);

    // inserts one at a time to make proper heap.
    insert(my_heap,69);
    insert(my_heap,29);
    insert(my_heap,50);
    insert(my_heap,94);
    insert(my_heap,6);
    insert(my_heap,19);
    insert(my_heap,55);
    insert(my_heap,76);
    insert(my_heap,57);
    insert(my_heap,71);
    insert(my_heap,75);
    insert(my_heap,10);
    insert(my_heap,85);
    insert(my_heap,67);
    insert(my_heap,4);

    // show full heap
    for(int i = 0; i < 15; i++){
        printf("%d ", my_heap[i]);
    }
    puts("");
    naive_heapsort(my_heap,15);
    // show sorted array
    for(int k = 0; k < 15; k++){
        printf("%d ", my_heap[k]);
    }
    */

    heap_config(MIN_HEAP,15); 
    int arr[] = {69,29,50,94,6,19,55,76,57,71,75,10,85,67,4};
    heapsort(arr,15);
    for(int k = 0; k < 15; k++){
        printf("%d ", arr[k]);
    }

    return EXIT_SUCCESS;
}
