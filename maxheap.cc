#include "maxheap.h"

// maxheap functions file

int test(){
    int test = 50000000;
    return test;
}

void BUILD_MAX_HEAP(struct SOC socArr[], int n){    // Function builds the max heap
    struct SOC temp;

    int start = (n/2) - 1;

    for(int i = start; i >= 0; i--){
        MAX_HEAPIFY(socArr, n, i);
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

void DELETE_MAX(struct SOC socArr[], int size, int topNumber, char key){ // Unfinished and untested Delete Max function!
    struct SOC last = socArr[size-1];
    

    if(key == 't'){
        if(size == NUM_OCC){
            printf("Top %d occupations in 1999 for total workers:\n"  ,topNumber);
        }
        int v = socArr[0].total;
        auto s = std::to_string(v);

        int n = s.length() - 3;
        int end = (v >= 0) ? 0 : 1; 
        while (n > end) {
            s.insert(n, ",");
            n -= 3;
        }
        
        std::cout << "\t" << socArr[0].occupation << ": " << s << std::endl;
        //printf("\t%s: %c\n" ,socArr[0].occupation, s);

        socArr[0] = last;

        MAX_HEAPIFY(socArr, size, 0);
    }
    else if(key == 'f'){
        printf("Top %d occupations from 1999 for female works:\n"  ,topNumber);
        printf("%s\n" , socArr[0].occupation);
        socArr[0] = last;

        size = size - 1;  // Decrement the size

        MAX_HEAPIFY(socArr, size, 0);
    }
    else if(key == 'm'){
        printf("Top %d occupations from 1999 for male works:\n"  ,topNumber);
        printf("%s\n" , socArr[0].occupation);
        socArr[0] = last;

        size = size - 1;  // Decrement the size

        MAX_HEAPIFY(socArr, size, 0);
    }
    else{
        printf("Error in delete_max has occured!");
    }    
}
