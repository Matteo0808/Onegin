#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "QuickSort.cpp"

void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize);
size_t RunThroughBuffer(char *Buffer, size_t bufSize);

int main(){

    int fileIn_Descriptor = open("onegin.txt", O_RDONLY);
    assert(fileIn_Descriptor != -1);
    
    FILE *fileIn = fdopen(fileIn_Descriptor, "r");
    assert(fileIn != NULL);

    struct stat fileStat = {};
    assert(fstat(fileIn_Descriptor, &fileStat) != -1);

    size_t fileSize = fileStat.st_size;

    char *bufferBeta = (char *)calloc(fileSize + 2, sizeof(char));
    assert(bufferBeta != NULL);

    bufferBeta[0] = '\0';
    bufferBeta[fileSize + 1] = '\0';

    char *Buffer = bufferBeta + 1;

    assert(setvbuf(fileIn, Buffer, _IONBF, fileSize) == 0);

    assert(read(fileIn_Descriptor, Buffer, fileSize) > 0);

    size_t arrSize = RunThroughBuffer(Buffer, fileSize);
    const char *arrLines[arrSize] = {};
    size_t arrElemSize = sizeof(arrLines[0]);

    BufferToLinesFragmentation(Buffer, arrLines, fileSize);

    printfArr(arrLines, arrSize, arrElemSize, "%s");

    size_t linesLen[arrSize] = {};
    for(int index = 0; index < arrSize; index++){
        linesLen[index] = strlen(arrLines[index]);
    }

    printfArr(linesLen, arrSize, sizeof(size_t), "%d");

    printf("hui1\n");

    QuickSort(arrLines, arrElemSize, 0, arrSize - 1, CompareStrOneginAscend);

    printf("hui2\n");

    int fileOut_Descriptor = open("onegin_out.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    assert(fileOut_Descriptor != -1);
    // if (fileOut_Descriptor == -1) {
    //     perror("open failed");
    //     fprintf(stderr, "errno = %d\n", errno);
    //     return 1;
    // }
    printf("hui3\n");
    for(int index = 0; index < arrSize; index++){
        write(fileOut_Descriptor, arrLines[index], linesLen[index]);
    }

    printf("hui4");
    //assert(write(fileOut_Descriptor, Buffer, fileSize) > 0);
    free(bufferBeta);
    close(fileOut_Descriptor);
    close(fileIn_Descriptor);
}

void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize){
    for(int index = -1; index < bufSize - 1; index++){
        if(Buffer[index] == '\0'){
            arrLines[index + 1] = Buffer + (index + 1);
        }
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