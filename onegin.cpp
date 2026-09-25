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

// struct Line{
//     const char *line;
//     size_t len;
// };

//TODO - struct!!!!!!!!!!!!!!!
//TODO - reverse sort, virginity text output, argc/argv

ErrSuc OpenInFile(const char *fileName, int *fileIn_Descriptor, size_t* fileSize);
ErrSuc ReadInFile(int fileIn_Descriptor, char *Buffer, size_t fileSize);
ErrSuc OpenOutFile(Line *arrLines, size_t arrSize);
void GetLens(Line *arrLines, size_t arrSize);
void BufferToLinesFragmentation(char *Buffer, Line *arrLines, size_t bufSize);
size_t RunThroughBuffer(char *Buffer, size_t bufSize);

int main(){

    // const char *arr1[4] = {"qweqweqwe1", "qweqweqwe12", "1", "qweeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee1"};
    // size_t arrSize1 = sizeof(arr1);
    // printfArr(arr1, arrSize1, sizeof(const char*), "%s");

    // printf("gay\n");

    // QuickSort(arr1, arrSize1, 0, arrSize1 - 1, CompareStrOneginAscend);

    // printfArr(arr1, arrSize1, sizeof(const char*), "%s");

    // return 0;

    int fileIn_Descriptor = 0; // TODO: fix naming
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

    // TODO: Buffer -> buffer
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

    // TODO: VLA - variable length array -- полное говно (budet crash), сделать calloc 
    ///@note completed
    
    Line *arrLines = (Line *)calloc(arrSize, sizeof(Line));
    
    // const char *arrLines[arrSize] = {};
    // size_t arrElemSize = sizeof(arrLines[0]);
    // size_t linesLen[arrSize] = {};

    printf("debug3\n");

    ///@note fragmentation buffer to lines
    BufferToLinesFragmentation(Buffer, arrLines, fileSize);

    printf("debug4\n");

    ///@note strlen of each line
    GetLens(arrLines, arrSize);

    printf("debug5\n");

    printfArr(&arrLines->len, arrSize, sizeof(Line), "%d");
    printfArr(&arrLines->line, arrSize, sizeof(Line), "%s");

    printf("hui1\n");

    QuickSort(arrLines, sizeof(const char *), 0, arrSize - 1, CompareStrOneginAscend);

    printf("hui2\n");

    switch (OpenOutFile(arrLines, arrSize)){
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
    // TODO: if style fix с пробелом везде сделай
    if(fstat(*fileIn_Descriptor, &fileStat) == -1) {return RETURN_ERROR_FSTAT;}

    *fileSize = fileStat.st_size;
    assert(*fileSize < 1<<32);
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

ErrSuc OpenOutFile(Line *arrLines, size_t arrSize){
    assert(arrLines != NULL);
    assert(linesLen != NULL);

    int fileOut_Descriptor = open("onegin_out.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if(fileOut_Descriptor == -1){
        close(fileOut_Descriptor);
        return RETURN_ERROR_FILECREATE;
    }
    
    for(size_t index = 0; index < arrSize; index++){
        if (write(fileOut_Descriptor, arrLines[index].line, arrLines[index].len) <= 0){
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
    for(size_t index = 0; index < bufSize; index++){
        if(Buffer[index] == '\r'){
            Buffer[index] = '\0';
        }
        if(Buffer[index] == '\n'){
            endlCount++;
            Buffer[index] = '\0';
            while((index + 1) < bufSize && Buffer[index + 1] == '\n'){
                Buffer[index + 1] = '\0';
                index++;
            }
        }
    }
    return endlCount;
}

void BufferToLinesFragmentation(char *Buffer, Line *arrLines, size_t bufSize){
    assert(Buffer != NULL);
    assert(arrLines != NULL);

    printf("%s\n", Buffer);
    printf("%p\n", arrLines);
    printf("%llu\n", bufSize);

    int linesIndex = 0;
    for(size_t index = -1; (int)index < (int)(bufSize - 1); index++){
        //printf("%d\n", index);
        //printf("123\n");
        if(Buffer[index] == '\0'){
            while((index + 1) < bufSize && Buffer[index + 1] == '\0'){
                //printf("huische\n");
                index++;
            }
            arrLines[linesIndex].line = Buffer + (index + 1);
            linesIndex++;
        }
    }
}

void GetLens(Line *arrLines, size_t arrSize){
    assert(linesLen != NULL);
    assert(arrLines != NULL);

    for(size_t index = 0; index < arrSize; index++){
        if(arrLines[index].line == 0){
            arrLines[index].len = 0;
        }
        else{
           arrLines[index].len = strlen(arrLines[index].line);
        }
    }
}