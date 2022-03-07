#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>


//void print_heap_node(SOC * heapPointer);        
void BUILD_MAX_HEAP(struct SOC socArr[], int n);    // Here all the functions needed to build the max heap are listed
void MAX_HEAPIFY(struct SOC socArr[], int i, int n);
void DELETE_MAX(struct SOC socArr[], int i, int n);