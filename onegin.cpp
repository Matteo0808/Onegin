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
    RETURN_ERROR = 1,
    RETURN_ERROR_FILEOPEN = 2,
    RETURN_ERROR_FSTAT = 3,
    RETURN_ERROR_FILEREAD = 4,
    RETURN_ERROR_FILECREATE = 5,
    RETURN_ERROR_FILEWRITE = 6
};

//TODO - struct!!!!!!!!!!!!!!!
//TODO - reverse sort, virginity text output, argc/argv

ErrSuc OpenInFile(const char *fileName, int *fileIn_Descriptor, size_t* fileSize);
ErrSuc ReadInFile(int fileIn_Descriptor, char *Buffer, size_t fileSize);
ErrSuc OpenOutFile(const char **arrLines, size_t *linesLen, size_t arrSize);
void GetLens(size_t *linesLen, const char **arrLines, size_t arrSize);
void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize);
size_t RunThroughBuffer(char *Buffer, size_t bufSize);

int main(){

    int fileIn_Descriptor = 0;
    size_t fileSize = 0;

    switch (OpenInFile("Onegin.txt", &fileIn_Descriptor, &fileSize)){
        case(RETURN_ERROR_FILEOPEN):
            printf("Error in input file opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FSTAT):
            printf("Error in input file opening in fuction fstat()\n");
            return RETURN_ERROR;
        default:
            break;
    }

    printf("debug0\n");
    
    char *bufferBeta = (char *)calloc(fileSize + 2, sizeof(char));
    assert(bufferBeta != NULL);
    
    printf("debug1\n");
    
    // bufferBeta[0] = '\0';
    // bufferBeta[fileSize + 1] = '\0';

    char *Buffer = bufferBeta + 1;
    assert(Buffer != NULL);

    switch (ReadInFile(fileIn_Descriptor, Buffer, fileSize)){
        case(RETURN_ERROR_FILEREAD):
            printf("Error in input file reading in fuction read()\n");
            return RETURN_ERROR;
        default:
            break;
    }

    ///@note writing buffer before sorting
    int fileOut_unsorted_Descriptor = open("onegin_out_unsorted.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOut_unsorted_Descriptor, Buffer, fileSize);

    // return 0;


    printf("debug2\n");

    ///@note changing '\r' and '\n' to '\0' and number of lines calculating
    size_t arrSize = RunThroughBuffer(Buffer, fileSize);

    ///@note writing buffer in one line
    int fileOut_in_one_line_Descriptor = open("onegin_out_in_one_line.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOut_in_one_line_Descriptor, Buffer, fileSize);

    // return 0;

    const char *arrLines[arrSize] = {};
    size_t arrElemSize = sizeof(arrLines[0]);
    size_t linesLen[arrSize] = {};

    printf("debug3\n");

    ///@note fragmentation buffer to lines
    BufferToLinesFragmentation(Buffer, arrLines, fileSize);

    printf("debug4\n");

    ///@note strlen of each line
    GetLens(linesLen, arrLines, arrSize);

    printf("debug5\n");

    printfArr(linesLen, arrSize, sizeof(size_t), "%d");
    printfArr(arrLines, arrSize, arrElemSize, "%s");

    printf("hui1\n");

    QuickSort(arrLines, arrElemSize, 0, arrSize - 1, CompareStrOneginAscend);

    printf("hui2\n");

    int fileOut_Descriptor = 0;
    switch (OpenOutFile(arrLines, linesLen, arrSize)){
        case(RETURN_ERROR_FILECREATE):
            printf("Error in input file creating or opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FILEWRITE):
            printf("Error in input file writing in fuction write()\n");
            return RETURN_ERROR;
        default:
            break;
    }
    
    free(bufferBeta);
}

ErrSuc OpenInFile(const char *fileName, int *fileIn_Descriptor, size_t* fileSize){
    assert(fileName != NULL);
    assert(fileIn_Descriptor != NULL);
    assert(fileSize != 0);
    
    *fileIn_Descriptor = open(fileName, O_RDONLY);
    if(*fileIn_Descriptor == -1) {return RETURN_ERROR_FILEOPEN;}
    
    // *fileIn = fdopen(*fileIn_Descriptor, "r");
    // if(*fileIn == NULL) {return RETURN_ERROR2;}

    struct stat fileStat = {};
    if(fstat(*fileIn_Descriptor, &fileStat) == -1) {return RETURN_ERROR_FSTAT;}

    *fileSize = fileStat.st_size;
    return RETURN_SUCCESS;
}

ErrSuc ReadInFile(int fileIn_Descriptor, char *Buffer, size_t fileSize){
    assert(Buffer != 0);
    // if(setvbuf(fileIn, Buffer, _IONBF, fileSize) == 0){
    //     close(fileIn_Descriptor);
    //     return RETURN_ERROR1;
    // }

    if(read(fileIn_Descriptor, Buffer, fileSize) <= 0){
        close(fileIn_Descriptor);
        return RETURN_ERROR_FILEREAD;
    }

    close(fileIn_Descriptor);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFile(const char **arrLines, size_t *linesLen, size_t arrSize){
    assert(arrLines != NULL);
    assert(linesLen != NULL);

    int fileOut_Descriptor = open("onegin_out.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if(fileOut_Descriptor == -1){
        close(fileOut_Descriptor);
        return RETURN_ERROR_FILECREATE;
    }
    
    for(int index = 0; index < arrSize; index++){
        if (write(fileOut_Descriptor, arrLines[index], linesLen[index]) <= 0){
            close(fileOut_Descriptor);
            return RETURN_ERROR_FILEWRITE;
        }
    }
    close(fileOut_Descriptor);
    return RETURN_SUCCESS;
}

size_t RunThroughBuffer(char *Buffer, size_t bufSize){
    assert(Buffer != NULL);

    size_t endlCount = 0;
    for(int index = 0; index < bufSize; index++){
        if(Buffer[index] == '\r'){
            Buffer[index] = '0';
        }
        if(Buffer[index] == '\n'){
            endlCount++;
            Buffer[index] = '\0';
            while(1){
                if(Buffer[index + 1] == '\n'){
                    Buffer[index + 1] = '\0';
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

void BufferToLinesFragmentation(char *Buffer, const char **arrLines, size_t bufSize){
    assert(Buffer != NULL);
    assert(arrLines != NULL);

    int linesIndex = 0;
    for(int index = -1; index < bufSize - 1; index++){
        printf("123");
        if(*(Buffer + index) == '\0'){
            while(*(Buffer + (index + 1)) == '\0' && (index + 1) < bufSize){
                printf("huische\n");
                index++;
            }
            *(arrLines + linesIndex) = Buffer + (index + 1);
            linesIndex++;
        }
    }
}

void GetLens(size_t *linesLen, const char **arrLines, size_t arrSize){
    assert(linesLen != NULL);
    assert(arrLines != NULL);

    for(size_t index = 0; index < arrSize; index++){
        if(arrLines[index] == 0){
            linesLen[index] = 0;
        }
        else{
           linesLen[index] = strlen(arrLines[index]);
        }
    }
}