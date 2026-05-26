#include <stdio.h>
#include <stdlib.h>
#include "../heap/heap.h"

/*  0-1 Knapsack
    Set S = {s1, s2, ..., sn} where each item si has a positive benefit (or value) vi and has a weight (or cost) wi.
    Take vi and wi to be integers. A maximum total weight, wmax.
    We need to choose a subset of S such that the total weight does not exceed
    wmax and the sum of the values vi is maximal.
*/

#define max(a, b) (((a) > (b)) ? (a) : (b))

int recursive_01_knapsack(int element, int weights[], int values[], int max_weight)
{
    // If there are no items or no weight we can't do anything
    if (element == 0 || max_weight == 0)
    {
        return 0;
    }

    // element bigger than knapsack itself, cant use it
    if (weights[element - 1] > max_weight)
    {
        return recursive_01_knapsack(element - 1, weights, values, max_weight);
    }

    // We check if we are better off including current element in knapsack or not
    int value_with_element = values[element - 1] + recursive_01_knapsack(element - 1, weights, values, max_weight - weights[element - 1]);
    int value_without_element = recursive_01_knapsack(element - 1, weights, values, max_weight);

    return (int)(max(value_with_element, value_without_element));
}

// assumes weights and values are in sorted order, wont work as of now since object is not specifed with density
int fractional_knapsack(int elements, int weights[], int values[], int max_weight)
{
    int max_value = 0;

    // calculate value density for each element and put them in a priority queue
    int *my_heap = malloc(sizeof(int) * elements);
    heap_config(MAX_HEAP, elements);

    for (int i = 0; i < elements; i++)
    {
        int density = values[i] / weights[i];
        insert(my_heap, density);
    }

    while (max_weight > 0)
    {
        int max_density = get_root(my_heap);
        delete_root(my_heap);
        if (max_density != 1)
        {
            if (weights[elements - 1] <= max_weight)
            {
                max_value += max_density * weights[elements - 1];
                max_weight -= weights[elements - 1];
            }
            else
            {
                max_value += max_density * max_weight;
                max_weight -= max_weight;
            }
            elements--;
        }
    }

    free(my_heap);
    return max_value;
}

int main(void)
{

    int elements = 3;
    int wmax = 50;

    /*
    int values[] = {100, 60, 120}; // values[i] corresponds to weights[i]
    int weights[] = {20, 10, 30};

    int optimal = recursive_01_knapsack(elements, weights, values, wmax);
    printf("Maximum value for this 0-1 Knapsack problem is %d\n", optimal);
    */

    int values[] = {120, 100, 60};
    int weights[] = {30, 20.10};

    int optimal = fractional_knapsack(elements, weights, values, wmax);
    printf("Maximum value for this frac Knapsack problem is %d\n", optimal);
    return EXIT_SUCCESS;
}
