/* Heap is a data structure that is represented as a complete binary tree and follows the heap property.
   The heap property can be one of the following:
   Max-heap: value of children nodes are less than the parent
   Min-heap: value of children nodes are greater than the parent
   One thing to note is that every node should have a greater or lesser value than it's descendants 
   depending on the heap property it follows.

   Heapsort is a sorting algorithm that uses a heap to sort sortable elements in either ascending or descending order.

   Using a heap we can implement a priority queue with O(log n) removal and addition. Much better than O(n) time using an 
   array!
*/

/* Heap operations defined
   insert, remove, heapify:
*/

/* Insert a new element in heap, and mantain heap property by swapping parent child nodes if required.
   Complexity is O(log n)
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t HEAP_PROPERTY;

#define MIN_HEAP 0
#define MAX_HEAP 1

int heap_size;
int heap_capacity;
HEAP_PROPERTY property;

void heap_config(HEAP_PROPERTY prop, int size){
    heap_size = 0;
    heap_capacity = size;
    if (prop == MIN_HEAP || prop == MAX_HEAP){
        property = prop;
    } else {
        puts("Invalid heap property!");
    }
}

void insert(int* heap, int value) {
    if (heap_size >= heap_capacity) {
        puts("Heap is full!");
        return;
    } 

    // Insert the node at the left-most avaliable position and let it up-heap bubble("bubble upwards")
    int curr_pos = heap_size++;
    heap[curr_pos] = value;

    if (property == MAX_HEAP){ // Satisfy max-heap property
        while(curr_pos > 0) {
            int parent_pos = (curr_pos - 1)/2; // get parent position, and swap until heap property is satisifed.
            if (heap[curr_pos] > heap[parent_pos]){
                swap(heap,curr_pos,parent_pos); // swap if parent is less than value we are inserting
                curr_pos = parent_pos; // Update where the value is now
            } else {
                break;
            }
        }
    } else if (property == MIN_HEAP) { // Satisfy min-heap property
        while(curr_pos > 0) {
            int parent_pos = (curr_pos - 1)/2; // get parent position, and swap until heap property is satisifed.
            if (heap[curr_pos] < heap[parent_pos]){
                swap(heap,curr_pos,parent_pos); // swap if parent is greater than value we are inserting
                curr_pos = parent_pos; // Update where the value is now
            } else {
                break;
            }
        }
    } else { // fallback
        puts("Invalid heap property!");
    }

}

/* Get the root and extract it from the heap. We replace it with the last node, and let down-heap bubbling occur to
   preserve heap property. It can be called extract_max or extract_min depending on the heap property.
   Complexity is O(log n)
*/
void delete_root(int* heap){
    if (heap_size == 0){
        puts("Heap is empty, nothing to delete!");
        return;
    }

    // Move last element to root
    swap(heap, 0, heap_size - 1);
    heap_size--; // Reduce heap size

    int curr = 0;

    if (property == MAX_HEAP){
        while (true){
            int left = 2 * curr + 1;
            int right = 2 * curr + 2;
            int largest = curr;

            if (left < heap_size && heap[left] > heap[largest]){ // check left child
                largest = left;
            }

            if (right < heap_size && heap[right] > heap[largest]){ // check right child
                largest = right;
            }

            if (largest == curr){
                break; // heap property satisfied
            }

            swap(heap, curr, largest);
            curr = largest;
        }
    } else if (property == MIN_HEAP){
        while (true){
            int left = 2 * curr + 1;
            int right = 2 * curr + 2;
            int largest = curr;

            if (left < heap_size && heap[left] < heap[largest]){ // check left child
                largest = left;
            }

            if (right < heap_size && heap[right] < heap[largest]){ // check right child
                largest = right;
            }

            if (largest == curr){ 
                break; // heap property satisfied
            }

            swap(heap, curr, largest);
            curr = largest;
        }
    } else { // fallback
        puts("Invalid heap property!");
    }
}

