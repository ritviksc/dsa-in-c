#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BASE 3
#define LOAD_FACTOR 0.85f
#define SCALE_FACTOR 2

typedef struct array
{
	void *dyn_arr;
	size_t element_size;
	size_t elements;
	size_t capacity;
} array_t;

array_t* init_array(size_t elem_size);
void array_add(array_t *arr, void *element);
ssize_t refactor_array(array_t *arr);
void del_array(array_t *arr);

array_t* init_array(size_t elem_size)
{
	if (!elem_size)
	{
		return NULL;
	}

	array_t *arr = malloc(sizeof(array_t));
	if (!arr)
	{
		perror("Malloc");
		return NULL;
	}

	void *data = malloc(elem_size * BASE);
	if (!data)
	{
		free(arr);
		perror("Malloc");
		return NULL;
	}
	arr->dyn_arr = data;
	arr->element_size = elem_size;
	arr->elements = 0;
	arr->capacity = BASE;

	return arr;

}

void array_add(array_t *arr, void *element)
{
	if (arr->elements >= arr->capacity)
	{
		ssize_t result = refactor_array(arr);
		if (result > 0)
		{
			puts("Reafactor\n");
			char *base = (char *)arr->dyn_arr;
    			char *dest = base + arr->elements * arr->element_size;
			memcpy(dest, element, arr->element_size);
			arr->elements++;
			return;
		} else 
		{
			return;
		}
	}

	 char *base = (char *)arr->dyn_arr;
         char *dest = base + arr->elements * arr->element_size;
         memcpy(dest, element, arr->element_size);
	 arr->elements++;

}

ssize_t refactor_array(array_t *arr)
{
	void *new = realloc(arr->dyn_arr, arr->element_size * (SCALE_FACTOR * arr->capacity));
	if (!new)
	{
		perror("Realloc");
		return -1;
	}
	arr->dyn_arr = new;
	arr->capacity = SCALE_FACTOR * arr->capacity;
	return 1;



}

void del_array(array_t *arr)
{
	if (arr)
	{
		if (arr->dyn_arr)
		{
			free(arr->dyn_arr);
		}
		free(arr);
	}

}


int main(void)
{
	array_t *array = init_array(sizeof(int));
	int w = 5;
	int x = 10;
	int y = 15;
	int z = 20;
	array_add(array,&w);
	array_add(array,&x);
	array_add(array,&y);
	array_add(array,&z);

	for(int i = 0; i < array->elements; i++)
	{
		int value = *(int *)((char *)array->dyn_arr + i * array->element_size);
		printf("%d ", value);
	}
	
}
