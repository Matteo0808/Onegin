//#define NDEBUG

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "printfArr.h"
#include "comparators.h"

void QuickSort(void *arr, size_t arrElemSize, size_t __left, size_t __right, int CompareFunc(const void* elem1, const void* elem2));
void Swap(void *elem1, void *elem2, size_t arrElemSize);


void QuickSort(void *arr, size_t arrElemSize, size_t __left, size_t __right, int CompareFunc(const void* elem1, const void* elem2)){
    assert(arr != NULL);

    if(__left >= __right){
        return;
    }
    size_t left = __left;
    size_t right = __right;

    void* pivot = malloc(arrElemSize);
    memcpy(pivot, (char *)arr + arrElemSize * ((__left + __right) / 2), arrElemSize);
    

    while(left <= right){
        assert(left <= right);
        
        while(CompareFunc((const void *)((char *)arr + arrElemSize * left), (const void *)pivot) < 0){
            left++;
        }

        while(CompareFunc((const void *)((char *)arr + arrElemSize * right), (const void *)pivot) > 0){
            right--;
            assert(right != ((size_t)-1));
        }

        if(right >= left){

            Swap((void *)((char *)arr + arrElemSize * left), (void *)((char *)arr + arrElemSize * right), arrElemSize);

            left++;

            if((ssize_t)right <= 0) {
                break;
            }
            
            right--;
        }
    }

    if(right > __left){
        QuickSort(arr, arrElemSize,  __left, right, CompareFunc);
    }
    if (left < __right){
        QuickSort(arr, arrElemSize, left, __right, CompareFunc);
    }

    free(pivot);
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
    // int main(){
    //     int arrInt[] = {2, 1, 6, 8, 2, 10, 1, 11};
    //     size_t arrElemIntSize = sizeof(arrInt[0]);
    //     size_t arrIntSize = sizeof(arrInt) / arrElemIntSize;
    
    //     const char* arrStr[] = {"str1", "2", "str3", "strstr4", "Str5"};
    //     size_t arrElemStrSize = sizeof(arrStr[0]);
    //     size_t arrStrSize = sizeof(arrStr) / arrElemStrSize;
    
    //     printfArr((void *)arrInt, arrIntSize, arrElemIntSize, "%d");
    //     printfArr((void *)arrStr, arrStrSize, arrElemStrSize, "%s");
    
    //     QuickSort(arrInt, arrElemIntSize, 0, arrIntSize - 1, CompareIntAscend);
    
    //     QuickSort(arrStr, arrElemStrSize, 0, arrStrSize - 1, CompareStrAscend);
    
    //     printfArr((void *)arrInt, arrIntSize, arrElemIntSize, "%d");
    //     printfArr((void *)arrStr, arrStrSize, arrElemStrSize, "%s");
    
    //     return 0;
    // }