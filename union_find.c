// Disjoint-set (union-find) - categorize objects (nodes) into diffrent sets and checks if two objects
// belong to same sets. Two objects belong to the same group if they have the same representative.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

// Function declarations
int* make(int n);
int** make_2(int n);
void create_union_1(int *reps, int length, int x, int y);
void create_union_2(int *reps,int x, int y);
void create_union_3(int *reps,int *rank,int x,int y);
int find_1(int *reps,int x);
int find_2(int *reps,int x);
void print_reps_1(int *reps, int size);
void print_reps_2(int *reps, int size);
void print_reps_rank(int *reps,int *ranks,int size);


// Make a set of n vertices with no edges between them
// For our case, we will treat natural numbers as our nodes (indices will represent them)
// Each index(vertice) has its representative stored
int* make_1(int n){
	int *vertices = malloc(sizeof(int) * n);
	if (!vertices)
	{
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) {
		vertices[i] = i;
	}
	return vertices;
}

// make with rank system to optmize find and unions
// return two arrays one corresponding to the reps and one corresponding with ranks
int** make_2(int n){
	int** arr = (int**)malloc(2 * sizeof(int*));
	if (!arr){
		exit(EXIT_FAILURE);
	}

	int *vertices = malloc(sizeof(int) * n);
        if (!vertices)
        {
		free(arr);
                exit(EXIT_FAILURE);
        }

	int *ranks = malloc(sizeof(int) * n);
	if (!ranks)
	{
		free(arr);
		free(vertices);
		exit(EXIT_FAILURE);
	}

        for (int i = 0; i < n; i++) {
                vertices[i] = i;
        }

	for (int i = 0; i < n; i++) {
		ranks[i] = 0;
	}

	arr[0] = vertices;
	arr[1] = ranks;
        return arr;


}

//------------------------------------------------------------------------------------------------

// First way of implementing union bewteen two nodes
// Complexity is O(n) but at worst each vertex needs a update so O(n^2)
// Not the best,we can do better
void create_union_1(int *reps, int length, int x, int y){
	int rx = reps[x];
	int ry = reps[y];

	if (rx == ry) return;

	for(int i = 0; i < length; i++) {
		if (reps[i] == rx) {
			reps[i] = ry;
		}
	}
}

// Set representative of x using find_2 and update it with representative of y
// Runs in O(n) - cost of find
void create_union_2(int *reps,int x,int y){
	reps[find_2(reps,x)] = reps[find_2(reps,y)];

}

void create_union_3(int *reps,int *rank,int x,int y){
	int rx = find_2(reps,x);
	int ry = find_2(reps,y);

	if (rx == ry) return;

	int rank_rx = rank[rx];
	int rank_ry = rank[ry];

	if (rank_rx > rank_ry){
		reps[ry] = rx;
	} else if (rank_rx < rank_ry){
		reps[rx] = ry;
	} else {
		reps[rx] = ry;
		rank[ry]++;
	}
}

//-------------------------------------------------------------------------------------------------

// If we find the union using the first way we can use this find to find representative 
// in constant time
int find_1(int *reps,int x) {
	return reps[x];
}

// If we store immediate representatives for each vertex we can trace back to main representative
// Runs at worst O(n) if we get basically create a list but wont happen on average but we can do 
// better
int find_2(int *reps,int x) {
	while (reps[x] != x){
		x = reps[x];
	}
	return x;

}

//--------------------------------------------------------------------------------------------------

void print_reps_1(int *reps, int size){
	for(int i =0; i < size; i++){
		printf("Vertex %d has representative %d\n",i,reps[i]);
	}
}

void print_reps_2(int *reps, int size){
        for(int i =0; i < size; i++){
                printf("Vertex %d has representative %d\n",i,find_2(reps,i));
        }
}

void print_reps_rank(int *reps,int *ranks,int size){
	for(int i =0; i < size; i++){
		 printf("Vertex %d has representative %d\n and rank %d\n",i,find_2(reps,i),ranks[i]);
	}

}

//-------------------------------------------------------------------------------------------------

int main(void) {

	int **arr = make_2(SIZE);
	create_union_3(arr[0],arr[1],6,8);
	create_union_3(arr[0],arr[1],3,4);
	create_union_3(arr[0],arr[1],7,1);
	create_union_3(arr[0],arr[1],7,4);
	create_union_3(arr[0],arr[1],1,8);


	print_reps_rank(arr[0],arr[1],SIZE);

	free(arr[0]);
	free(arr[1]);
	free(arr);
	return EXIT_SUCCESS;
}

