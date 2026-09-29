//#define NDEBUG

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXSIZE 1<<16
#include "comparators.h"

void QuickSort(void *arr, size_t arrElemSize, ssize_t left, ssize_t right, int CompareFunc(const void* elem1, const void* elem2));
void Swap(void *elem1, void *elem2, size_t arrElemSize);

void QuickSort(void *arr, size_t arrElemSize, ssize_t left, ssize_t right, int CompareFunc(const void* elem1, const void* elem2)){
    
    if(left >= right){
        return;
    }
    
    size_t last = 0;

    Swap((void *)((char *)arr + arrElemSize * left), (void *)((char *)arr + arrElemSize * ((left + right) / 2)), arrElemSize);

    last = left;

    for(ssize_t index = left + 1; index <= right; index++){
        if(CompareFunc((const void *)((char *)arr + arrElemSize * index), (const void *)((char *)arr + arrElemSize * left)) < 0){
            Swap((void *)((char *)arr + arrElemSize * (++last)), (void *)((char *)arr + arrElemSize * index), arrElemSize);
        }
    }

    Swap((void *)((char *)arr + arrElemSize * left), (void *)((char *)arr + arrElemSize * last), arrElemSize);

    if (left < last - 1){
        QuickSort(arr, arrElemSize, left, last - 1, CompareFunc);
    }

    if (left + 1 < right){
        QuickSort(arr, arrElemSize, last + 1, right, CompareFunc);
    }

}

void Swap(void* elem1, void* elem2, size_t arrElemSize){
    assert(elem1 != 0);
    assert(elem2 != 0);

    char temp[MAXSIZE];
    
    if(arrElemSize > MAXSIZE){
        // TODO: 
    }
    memcpy(temp, elem2, arrElemSize);
    memcpy(elem2, elem1, arrElemSize);
    memcpy(elem1, temp, arrElemSize);
}