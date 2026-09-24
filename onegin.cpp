#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "QuickSort.cpp"

enum ErrSuc{
    RETURN_SUCCESS = 0,
    RETURN_ERROR = 1
};

ErrSuc OpenInFile(const char *fileName, int *fileIn_Descriptor, FILE *fileIn, size_t* fileSize);
ErrSuc ReadInFile(int fileIn_Descriptor, FILE *fileIn, char *Buffer, size_t fileSize);
ErrSuc OpenOutFile(const char **arrLines, size_t *linesLen, size_t arrSize);
void GetLens(size_t *linesLen, const char **arrLines, size_t arrSize);
void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize);
size_t RunThroughBuffer(char *Buffer, size_t bufSize);

int main(){

    int fileIn_Descriptor = 0;
    FILE *fileIn;
    size_t fileSize = 0;
    if (OpenInFile("Onegin.txt", &fileIn_Descriptor, fileIn, &fileSize) == RETURN_ERROR){
        printf("Error in input file opening\n");
        return RETURN_ERROR;
    }

    char *bufferBeta = (char *)calloc(fileSize + 2, sizeof(char));
    assert(bufferBeta != NULL);

    bufferBeta[0] = '\0';
    bufferBeta[fileSize + 1] = '\0';

    char *Buffer = bufferBeta + 1;

    if (ReadInFile(fileIn_Descriptor, fileIn, Buffer, fileSize) == RETURN_ERROR){
        printf("Error in input file reading\n");
        return RETURN_ERROR;
    }

    size_t arrSize = RunThroughBuffer(Buffer, fileSize);

    const char *arrLines[arrSize] = {};
    size_t arrElemSize = sizeof(arrLines[0]);
    size_t linesLen[arrSize] = {};

    BufferToLinesFragmentation(Buffer, arrLines, fileSize);

    GetLens(linesLen, arrLines, arrSize);

    printfArr(arrLines, arrSize, arrElemSize, "%s");
    printfArr(linesLen, arrSize, sizeof(size_t), "%d");

    printf("hui1\n");

    QuickSort(arrLines, arrElemSize, 0, arrSize - 1, CompareStrOneginAscend);

    printf("hui2\n");

    int fileOut_Descriptor = 0;
    if (OpenOutFile(arrLines, linesLen, arrSize) == RETURN_ERROR){
        printf("Error in output file creating, opening or writing\n");
        return RETURN_ERROR;
    }
    
    free(bufferBeta);
}

ErrSuc OpenInFile(const char *fileName, int *fileIn_Descriptor, FILE *fileIn, size_t* fileSize){
    
    *fileIn_Descriptor = open(fileName, O_RDONLY);
    if(*fileIn_Descriptor == -1) {return RETURN_ERROR;}
    
    fileIn = fdopen(*fileIn_Descriptor, "r");
    if(fileIn == NULL) {return RETURN_ERROR;}

    struct stat fileStat = {};
    if(fstat(*fileIn_Descriptor, &fileStat) == -1) {return RETURN_ERROR;}

    *fileSize = fileStat.st_size;
    return RETURN_SUCCESS;
}

ErrSuc ReadInFile(int fileIn_Descriptor, FILE *fileIn, char *Buffer, size_t fileSize){
    if(setvbuf(fileIn, Buffer, _IONBF, fileSize) == 0){
        close(fileIn_Descriptor);
        return RETURN_ERROR;
    }

    if(read(fileIn_Descriptor, Buffer, fileSize) > 0){
        close(fileIn_Descriptor);
        return RETURN_ERROR;
    }

    close(fileIn_Descriptor);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFile(const char **arrLines, size_t *linesLen, size_t arrSize){
    int fileOut_Descriptor = open("onegin_out.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if(fileOut_Descriptor == NULL){
        close(fileOut_Descriptor);
        return RETURN_ERROR;
    }
    
    for(int index = 0; index < arrSize; index++){
        if (write(fileOut_Descriptor, arrLines[index], linesLen[index]) <= 0){
            close(fileOut_Descriptor);
            return RETURN_ERROR;
        }
    }
    close(fileOut_Descriptor);
    return RETURN_SUCCESS;
}

void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize){
    for(int index = -1; index < bufSize - 1; index++){
        if(Buffer[index] == '\0'){
            arrLines[index + 1] = Buffer + (index + 1);
        }
    }
}

void GetLens(size_t *linesLen, const char **arrLines, size_t arrSize){
    for(int index = 0; index < arrSize; index++){
        linesLen[index] = strnlen(arrLines[index], MAXSIZE);
    }
}

size_t RunThroughBuffer(char *Buffer, size_t bufSize){
    size_t endlCount = 0;
    for(int index = 0; index < bufSize; index++){
        if(Buffer[index] == '\n'){
            endlCount++;
            Buffer[index] = '\0';
            int jindex = 0;
            while(1){
                jindex++;
                if(Buffer[index + jindex] == '\n'){
                    index++;
                }
                else{
                    break;
                }
            }
        }
    }
    return endlCount;
}