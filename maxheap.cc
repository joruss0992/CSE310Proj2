#include "maxheap.h"

// maxheap functions file

// Commented out function was given as example from TA Michael
// void print_heap_node(SOC * heapPointer){
//     std::cout << heapPointer->occupation << std::endl;
//     std::cout << heapPointer->SOC_code << std::endl;
//     std::cout << heapPointer->total << std::endl;
//     std::cout << heapPointer->female << std::endl;
//     std::cout << heapPointer->male << std::endl;
// }

void BUILD_MAX_HEAP(struct SOC socArr[], int n){    // Function builds the max heap
    struct SOC temp;
    for(int i = n/2-1; i >= 0; i--){   
        MAX_HEAPIFY(socArr, n, i);
    }
    for(int i = n-1; i > 0; i--){
        temp = socArr[0];
        socArr[0] = socArr[i];
        socArr[i] = temp;

        MAX_HEAPIFY(socArr, i, 0);
    }
}

void MAX_HEAPIFY(struct SOC socArr[], int i, int n){    // Max Heapify function to swap the values according to their total
    struct SOC temp;
    int largest = n;
    int l = 2 * n + 1;
    int r = 2 * n + 2;

    if(l < i && socArr[l].total > socArr[largest].total)
        largest = l;

    if(r < i && socArr[r].total > socArr[largest].total)
        largest = r;

    if (largest != n){
        temp = socArr[n];
        socArr[n] = socArr[largest];
        socArr[largest] = temp;

        MAX_HEAPIFY(socArr, i, largest);
    }
}

void DELETE_MAX(struct SOC socArr[], int i, int n){ // Unfinished and untested Delete Max function!
    struct SOC last = socArr[i-1];

    printf("Top %d occupations from 1999 for "  ,n);

    socArr[0] = last;

    i = i - 1;  // Decrement the size

    MAX_HEAPIFY(socArr, i, 0);
}