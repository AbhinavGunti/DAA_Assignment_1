// Name: ABHINAV GUNTI
// SRN: PES1UG20CS008
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */


//helper function to heapify the max heap
static int heapify(heap_t *heap)
{
    int c=0,num=heap->size,child,parent,in;
	//we build heap from the array heap
    //we iterate  through parent and child and child 
    //to place the element in the right place in a correct order
	for(int k=num/2-1;k>=0;k--){//last non leaf node is given by num/2
		parent=k;               //index of left child: 2i+1,index of right child : 2i+2
	    in=heap->arr[parent];
		child=2*parent+1;       
		while(child<num) {      //child needs to be lesser
			if(child+1<num) {
				if(heap->arr[child+1]>heap->arr[child]){
					child++;
                }
			}
			if(in>heap->arr[child]){
				break;
            }
			heap->arr[parent]=heap->arr[child];
			parent=child;
			child=2*parent+1;
            c=c+1;  
		}
		heap->arr[parent]=in;
	}
     return c;
}

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size) {
    heap->size = 0;     //initialize size to zero
    heap->max_size = max_size;      
    heap->arr = (int*)malloc(max_size*sizeof(int));     //allocate space dynamically
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) {
    heap->size=heap->size+1;
    heap->arr[heap->size - 1] = key;
    *count_ptr=heapify(heap);       //we call heapify to fill up the max heap
}

static void exchange(int *maximum, int *minimum){
	int ele;
    ele = *maximum;        //to swap largest with current element(minimum)
	*maximum = *minimum;
	*minimum = ele; //minimum holds the maximum after swap
}
// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr) {
	int maximum;
    maximum= heap->arr[0];     //taking 1st element as the max element initially
	exchange(&heap->arr[0], &heap->arr[heap->size-1]);  //swapping the larger of the two elements
	heap->size--;       //we need to decrement the size of the heap
	*count_ptr = heapify(heap);     //we call hapify function
	return maximum;     //we return the maximum element
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) {
	int data;
    data= -1;
	for (int i = 0; i < heap->size; i++){
		++(*count_ptr); //we increment the count_ptr pointer value because a comparision is being performed below in if statement
		if(heap->arr[i] == key){    //if element is found
			data = key;
        }
	}
	return data; //element has the desired key and we return it
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) {
    //we iterate throught the array to find the min element
	int minimum;
    minimum = heap->arr[heap->size/2];  
	for(int i = heap->size/2; i < heap->size; i++){
		(*count_ptr)++;     ////we increment the count_ptr pointer value because a comparision is being performed below in if statement
		if(heap->arr[i] < minimum){
			minimum = heap->arr[i];
		}
	}
	return minimum;     //return ing the min value
}
// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr) {
	(*count_ptr)++;     //increment count_ptr pointer value
	return heap->arr[0];        //max elementis stored in index 0 since it is a max heap
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) {
    heap->size=0;       //initialize size to 0
	heap->arr = NULL;	     //we need to initialize it to null before freeing
    free(heap->arr);         //we deallocatet the memory
}
// Clears the heap for reuse
void clear_heap(heap_t *heap) {
	free(heap->arr);        //we deallocatet the memory
	heap->size = 0;         //again initialize the size to 0 so that we can reuse
    heap->arr = (int*)malloc(heap->max_size*sizeof(int));   //allocate space dynamically
}  
// Name: ABHINAV GUNTI
// SRN: PES1UG20CS008