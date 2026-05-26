#include <stdio.h>
#include <stdlib.h>

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

    // We check if we are better of including current element in knapsack or not
    int value_with_element = values[element - 1] + recursive_01_knapsack(element - 1, weights, values, max_weight - weights[element]);
    int value_without_element = recursive_01_knapsack(element - 1, weights, values, max_weight);

    return (int)(max(value_with_element, value_without_element));
}

int main(void)
{

    int elements = 3;

    int values[] = {100, 60, 120}; // values[i] corresponds to weights[i]
    int weights[] = {20, 10, 30};

    int wmax = 50;

    int optimal = recursive_01_knapsack(elements, weights, values, wmax);
    printf("Maximum value for this 0-1 Knapsack problem is %d", optimal);

    return EXIT_SUCCESS;
}