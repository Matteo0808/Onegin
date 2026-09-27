//#define NDEBUG

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "printfArr.h"
#include "comparators.h"

void QuickSort(void *arr, size_t arrElemSize, ssize_t left, ssize_t right, int CompareFunc(const void* elem1, const void* elem2));
void Swap(void *elem1, void *elem2, size_t arrElemSize);


// void QuickSort(void *arr, size_t arrElemSize, size_t __left, size_t __right, int CompareFunc(const void* elem1, const void* elem2)){
//     assert(arr != NULL);

//     if(__left >= __right){
//         return;
//     }
//     size_t left = __left;
//     size_t right = __right;

//     void* pivot = malloc(arrElemSize);
//     memcpy(pivot, (char *)arr + arrElemSize * ((__left + __right) / 2), arrElemSize);
    

//     while(left <= right){
//         assert(left <= right);
        
//         printf("meow1\n");
        
//         // printf("str1 = [%p]\n", (char *)arr + arrElemSize * left);
//         // printf("str2 = [%p]\mn", pivot);

//         printf("comp_l = %d\n", CompareFunc((const void *)((char *)arr + arrElemSize * left), (const void *)pivot));
//         while(CompareFunc((const void *)((char *)arr + arrElemSize * left), (const void *)pivot) <= 0 && left < __right){
//             printf("left = %d", left);
//             left++;
//         }

//         printf("meow2\n");

//         // printf("right = %d\n", right);
//         // printf("el_size = %d\n", arrElemSize);
//         // printf("str1 = [%p]\n", (char *)arr + arrElemSize * right);
//         // printf("str2 = [%p]\n", pivot);



//         printf("comp_r = %d\n", CompareFunc((const void *)((char *)arr + arrElemSize * right), (const void *)pivot));
//         while(CompareFunc((const void *)((char *)arr + arrElemSize * right), (const void *)pivot) > 0){
//             right--;
//             printf("right = %d", right);
//             assert(right != ((size_t)-1));
//         }

//         printf("meow3\n");

//         if(right >= left){

//             printf("__left = %d\n__right = %d\nleft = %d\nright = %d\n", __left, __right, left, right);
//             Swap((void *)((char *)arr + arrElemSize * left), (void *)((char *)arr + arrElemSize * right), arrElemSize);

//             left++;
            
//             right--;
//         }
//     }

//     if(right > __left){
//         QuickSort(arr, arrElemSize,  __left, right, CompareFunc);
//     }
//     if (left < __right){
//         QuickSort(arr, arrElemSize, left, __right, CompareFunc);
//     }

//     free(pivot);
// }

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