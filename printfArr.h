#ifndef PRINTFARR_H
#define PRINTFARR_H

#include <stdio.h>
#include <assert.h>

#define MAXSIZE 16384

enum dataType{
    INT,
    DOUBLE,
    CHAR,
    STRING
    //for
};

void printfArr(void* arr, size_t arrSize, size_t arrElemSize, const char* spezificator);
void printfArrDebug(void* arr, size_t arrSize, size_t arrElemSize, const char* format,
                    void FormatFunc(const void *elem, char *buf, size_t bufSize));


void printfArr(void* arr, size_t arrSize, size_t arrElemSize, const char* format){
    assert(arr != NULL);
    assert(format != NULL);

    char strRes[MAXSIZE];
    printf("\n=======================================================================================\n");
    printf("Array: \n");
    for(int index = 0; index < arrSize; index++){
        assert(index >= 0 && index < arrSize);

        snprintf(strRes, MAXSIZE, "[Elem %d]: %s\t", index, format);
        assert(strRes != 0);
        printf(strRes, *((char**)((char *)arr + index * arrElemSize)));
    }
    printf("\n=======================================================================================\n");
}


void printfArrDebug(void* arr, size_t arrSize, size_t arrElemSize, const char* format,
                    void FormatFunc(const void *elem, char *buf, size_t bufSize)){
    assert(arr != NULL);
    assert(format != NULL);

    int lens[MAXSIZE] = {};
    char strInd[MAXSIZE] = {};
    int lensElemStr[MAXSIZE] = {};
    char strRes[MAXSIZE];

    // char strFormat[MAXSIZE];
    // snprintf(strFormat, MAXSIZE, "%s ", format);

    for(int index = 0; index < arrSize; index ++){
        FormatFunc((const char *)arr + arrElemSize * index, strInd, MAXSIZE);
        lens[index] = strlen(strInd);
        lensElemStr[index] = snprintf(NULL, 0, "[elem %d:]", index);
    }


    printf("\n===============================================================================================================\n");
    printf("Array: \n");
    for(int index = 0; index < arrSize; index++){
        if(lens[index] <= lensElemStr[index]){
            printf("[elem %d:] ", index);
        }
        else{
            printf("[elem %d:]", index);
            for(int jindex = 0; jindex < lens[index] - lensElemStr[index]; jindex++){
                printf(" ");
            }
        }
        
    }

    printf("\n");

    for(int index = 0; index < arrSize; index++){
        if(lens[index] > lensElemStr[index]){
            FormatFunc(((const char *)arr + arrElemSize * index), strRes, MAXSIZE);
            printf(strRes);
        }
        else{
            FormatFunc(((const char *)arr + arrElemSize * index), strRes, MAXSIZE);
            printf(strRes);
            for(int jindex = 0; jindex < (lensElemStr[index] - lens[index]) + 1; jindex++){
                printf(" ");
            }
        }
        
    }

    printf("\n===============================================================================================================\n");
}


void FormatInt(const void *elem, char *buf, size_t bufSize){
    snprintf(buf, bufSize, "%d", *((const int *)elem));
}

#endif