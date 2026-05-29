#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000
#define TRIALS 50

int cmp(const void *a, const void *b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;
    return x - y;
}

int is_equal(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

void copy_array(int *src, int *dst, int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}	

int pt(int a[], int l, int r)
{
    int pivot = a[r];
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[r]);
    return i + 1;
}

void qsortO(int a[], int l, int r)
{
    if (l < r)
    {
        int p = pt(a, l, r);
        qsortO(a, l, p - 1);
        qsortO(a, p + 1, r);
    }
}

int partition(int array[], int start, int end)
{
	int p = end;
	for (int i = start; i <= end; i++){
		if (array[i] >= array[end]){
			swap(&array[i],&array[end]);
			p = i;	
		}
	}
				
	return p;
}

void quicksort(int array[], int start, int end)
{
	if (start < end){
		int p = partition(array,start,end);
		quicksort(array,start,p-1);
		quicksort(array,p+1,end);
	}
}

void make_nearly_sorted(int *a)
{
    for (int i = 0; i < N; i++)
        a[i] = i;

    for (int i = 0; i < N; i++)
    {
        int j = i + (rand() % 7 - 3); // small disorder window
        if (j >= 0 && j < N)
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
}

// ---------------- MAIN BENCHMARK ----------------

int main()
{
    srand(time(NULL));

    double total_my = 0;
    double total_qs = 0;

    int a[N], b[N];

    for (int t = 0; t < TRIALS; t++)
    {
        make_nearly_sorted(a);

        for (int i = 0; i < N; i++)
            b[i] = a[i];

        clock_t start, end;

        // ---- qsort ----
        start = clock();
        qsortO(a,0,N-1);
        end = clock();
        total_qs += (double)(end - start) / CLOCKS_PER_SEC;

        // ---- your quicksort ----
        start = clock();
        quicksort(b, 0, N - 1);
        end = clock();
        total_my += (double)(end - start) / CLOCKS_PER_SEC;
    }

    printf("Average default quicksort algorithm timing for %d trials: %f sec\n",TRIALS, total_qs / TRIALS);
    printf("Average custom quicksort algorithm timing for %d trials: %f sec\n", TRIALS,total_my / TRIALS);

    return 0;
}
