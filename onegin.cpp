#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

struct Line{
    const char *line;
    size_t len;
};

#include "QuickSort.cpp"

struct Info{
    int fileInDescriptor;
    size_t fileSize;
    char *buffer;
    size_t arrSize;
    Line* arrLines;
};

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
///@note completed

//TODO - reverse sort, virginity text output, argc/argv

ErrSuc OpenInFile(const char *fileName, int *fileInDescriptor, size_t* fileSize);
ErrSuc ReadInFile(int fileInDescriptor, char **buffer, size_t fileSize);
ErrSuc OpenOutFile(Line *arrLines, size_t arrSize);
void GetLenghts(Line *arrLines, size_t arrSize);
void BufferToLinesFragmentation(char *buffer, Line *arrLines, size_t bufSize, size_t arrSize);
size_t RunThroughBuffer(char *buffer, size_t bufSize);
void ProgramDestroy(Info *programInfo, char *buffer, Line* arrLines);

int main(){
    //TODO: main
    ///@note completed

    //TODO: onegin 2 strings - WORKING!!!
    ///@note completed

    //TODO: isolate comparator - WORKING!!!
    ///@note completed

    //TODO: qsort() standart - my qsort ne workaet

    //TODO: before write runtroughtbuffer \0 -> \n

    //TODO: func args in one struct

    //TODO: errors

    //TODO: sprintf() вместо write / File* вместо descr, ask ded


    // const char *str[4] = {"qweqweqwe1", "qweqweqwe12", "1", "qweeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee1"};
    // size_t arrElemSize1 = sizeof(str[0]);
    // size_t arrSize1 = sizeof(str) / arrElemSize1;

    // printf("gay\n");

    // QuickSort(str, arrElemSize1, 0, arrSize1 - 1, CompareStrOneginAscend);

    // printf("%s\n", str[0]);
    // printf("%s\n", str[1]);
    // printf("%s\n", str[2]);
    // printf("%s\n", str[3]);
    

    // return 0;

    // const char *str[] = {"strstrstrstrstsrtrstrstsr", "str"};

    // QuickSort(str, sizeof(const char *), 0, 1, CompareStrOneginAscend);

    // printf("%s\n", str[0]);
    // printf("%s\n", str[1]);
    


    // return 0;




    // TODO: fix naming
    ///@note compleeted

    Info programInfo = {}; 

    switch (OpenInFile("Onegin.txt", &(programInfo.fileInDescriptor), &(programInfo.fileSize))){
        case(RETURN_ERROR_FILEOPEN):
            printf("Error in input file opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FSTAT):
            printf("Error in input file opening in fuction fstat()\n");
            return RETURN_ERROR;
        default:
            break;
    }    
    
    
    // bufferBeta[0] = '\0';
    //bufferBeta[fileSize + 1] = '\n';

    // TODO: Buffer -> buffer
    ///@note completed

    // char *buffer = bufferBeta + 1;
    // assert(buffer != NULL);

    switch (ReadInFile(programInfo.fileInDescriptor, &programInfo.buffer, programInfo.fileSize)){
        case(RETURN_ERROR_FILEREAD):
            printf("Error in input file reading in fuction read()\n");
            return RETURN_ERROR;
        default:
            break;
    }

    //printf("buf in main() = %p\n", programInfo.buffer);

    ///@note writing buffer before sorting
    int fileOut_unsorted_Descriptor = open("onegin_out_unsorted.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOut_unsorted_Descriptor, programInfo.buffer, programInfo.fileSize);


    ///@note changing '\r' and '\n' to '\0' and number of lines calculating
    programInfo.arrSize = RunThroughBuffer(programInfo.buffer, programInfo.fileSize);


    ///@note writing buffer in one line
    int fileOut_in_one_line_Descriptor = open("onegin_out_in_one_line.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOut_in_one_line_Descriptor, programInfo.buffer, programInfo.fileSize);

    // return 0;

    // TODO: VLA - variable length array -- полное говно (budet crash), сделать calloc
    ///@note completed
    

    programInfo.arrLines = (Line *)calloc(programInfo.arrSize, sizeof(Line));
    
    // const char *arrLines[arrSize] = {};
    // size_t arrElemSize = sizeof(arrLines[0]);
    // size_t linesLen[arrSize] = {};

    printf("debug3\n");

    

    ///@note fragmentation buffer to lines
    BufferToLinesFragmentation(programInfo.buffer, programInfo.arrLines, programInfo.fileSize, programInfo.arrSize);

    

    printf("debug4\n");

    
    //GetLenghts(programInfo.arrLines, programInfo.arrSize);

    printf("debug5\n");

    //QuickSort(programInfo.arrLines, sizeof(const char *), 0, programInfo.arrSize - 1, CompareStrOneginAscend);

    qsort(programInfo.arrLines, programInfo.arrSize, sizeof(Line), CompareStrOneginAscend);

    printf("hui2\n");

    switch (OpenOutFile(programInfo.arrLines, programInfo.arrSize)){
        case(RETURN_ERROR_FILECREATE):
            printf("Error in input file creating or opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FILEWRITE):
            printf("Error in input file writing in fuction write()\n");
            return RETURN_ERROR;
        default:
            break;
    }
    
    ProgramDestroy(&programInfo, programInfo.buffer, programInfo.arrLines);
}

ErrSuc OpenInFile(const char *fileName, int *fileInDescriptor, size_t* fileSize){
    assert(fileName != NULL);
    assert(fileInDescriptor != NULL);
    assert(fileSize != 0);
    
    *fileInDescriptor = open(fileName, O_RDONLY);
    if (*fileInDescriptor == -1) {return RETURN_ERROR_FILEOPEN;}
    
    // *fileIn = fdopen(*fileInDescriptor, "r");
    // if(*fileIn == NULL) {return RETURN_ERROR2;}

    struct stat fileStat = {};
    // TODO: if style fix с пробелом везде сделай
    if (fstat(*fileInDescriptor, &fileStat) == -1) {return RETURN_ERROR_FSTAT;}

    *fileSize = fileStat.st_size;
    assert(*fileSize < 4294967296ULL /*1<<32*/);
    return RETURN_SUCCESS;
}

ErrSuc ReadInFile(int fileInDescriptor, char **buffer, size_t fileSize){

    char *bufferBeta = (char *)calloc(fileSize + 2, sizeof(char));
    assert(bufferBeta != NULL);

    //printf("bufBeta = %p\n", bufferBeta);

    *buffer = bufferBeta + 1;
    assert(*buffer != NULL);

    //printf("buf = %p\n", *buffer);

    if (read(fileInDescriptor, *buffer, fileSize) <= 0){
        close(fileInDescriptor);
        return RETURN_ERROR_FILEREAD;
    }
    

    close(fileInDescriptor);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFile(Line *arrLines, size_t arrSize){
    assert(arrLines != NULL);
    printf("OpenOutFile\n");
    int fileOut_Descriptor = open("onegin_out.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fileOut_Descriptor == -1){
        close(fileOut_Descriptor);
        return RETURN_ERROR_FILECREATE;
    }
    
    for (size_t index = 0; index < arrSize; index++){
        if (write(fileOut_Descriptor, arrLines[index].line, arrLines[index].len) <= 0){
            close(fileOut_Descriptor);
            return RETURN_ERROR_FILEWRITE;
        }
    }
    close(fileOut_Descriptor);
    return RETURN_SUCCESS;
}

size_t RunThroughBuffer(char *buffer, size_t bufSize){

    size_t endlCount = 0;
    for (size_t index = 0; index < bufSize; index++){
        if (buffer[index] == '\r'){
            buffer[index] = '\0';
        }
        if (buffer[index] == '\n'){
            endlCount++;
            buffer[index] = '\0';
            while((index + 1) < bufSize && buffer[index + 1] == '\n'){
                buffer[index + 1] = '\0';
                index++;
            }
        }
    }
    return endlCount;
}

void BufferToLinesFragmentation(char *buffer, Line *arrLines, size_t bufSize, size_t arrSize){
    assert(buffer != NULL);
    assert(arrLines != NULL);

    printf("buffer = [%s]\n", buffer);
    printf("arrLines ptr = %p\n", arrLines);
    printf("bufSize = %llu\n", bufSize);

    int linesIndex = 0;

    //
    for (ssize_t index = -1; index < (ssize_t)(bufSize - 1); index++){
        // printf("%d\n", index);
        // printf("%c\n", buffer[index]);
        
        if (buffer[index] == '\0'){
            //printf("yes\n");
            while((index + 1) < (ssize_t)bufSize && buffer[index + 1] == '\0'){
                //printf("huische\n");
                index++;
                //printf("%d\n", index);
            }
            arrLines[linesIndex].line = buffer + (index + 1);
            //printf("%s\n", arrLines[linesIndex].line);
            linesIndex++;
            //printf("%d\n\n", linesIndex);
        }
    }
    printf("hey\n");
    GetLenghts(arrLines, arrSize);

}

void GetLenghts(Line *arrLines, size_t arrSize){
    assert(arrLines != NULL);


    for (size_t index = 0; index < arrSize; index++){
        if (arrLines[index].line == 0){
            arrLines[index].len = 0;
        }
        else{
            if(index == 0){
                arrLines[index].len = strlen(arrLines[index].line);
            }
            else{
                arrLines[index].len = arrLines[index].line - arrLines[index - 1].line;
                //TODO
                ///@note completed
            }
        }
    }
}

void ProgramDestroy(Info *programInfo, char *buffer, Line* arrLines){
    free(buffer - 1);
    free(arrLines);
    programInfo->arrSize = 0;
    programInfo->fileInDescriptor = -1;
    programInfo->fileSize = -1;
}