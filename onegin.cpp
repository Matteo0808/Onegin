#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

struct Line{
    char *line;
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
    RETURN_ERROR_FILEWRITE_TASK1 = 6,
    RETURN_ERROR_TOO_LARGE_FILE_SIZE = 7,
    RETURN_ERROR_MEMORY_ALLOCATION = 8,
    RETURN_ERROR_FILEADD_TASK2 = 9,
    RETURN_ERROR_FILEWRITE_TASK2 = 10,
    RETURN_ERROR_FILEADD_TASK3 = 11,
    RETURN_ERROR_FILEWRITE_TASK3 = 12
};


//TODO - struct!!!!!!!!!!!!!!! 
///@note completed

//TODO - reverse sort
///@note completed

//TODO - virginity text output
///@note completed fuck you bitch


//TODO: main clear
///@note completed

//TODO: onegin 2 strings - WORKING!!!
///@note completed

//TODO: isolate comparator - WORKING!!!
///@note completed

//TODO: qsort() standart - my qsort ne workaet - vse, teper' workaet
///@note completed

//TODO: before write runtroughtbuffer \0 -> \n - found more optimal solution
///@note completed


//TODO: errors
///@note completed

//TODO: sprintf() вместо write / File* вместо descr, ask ded
///@note completed

// TODO: fix naming
///@note compleeted

//TODO - argc/argv - in progress

//TODO - README - in progress

//TODO: func args in one struct - in progress

//TODO - clear project

ErrSuc OpenInFile(const char *fileName, int *fileInDescriptor, size_t* fileSize);
ErrSuc ReadInFile(int fileInDescriptor, char **buffer, size_t fileSize);
ErrSuc OpenOutFileTask1(Line *arrLines, size_t arrSize);
ErrSuc OpenOutFileTask2(Line *arrLines, size_t arrSize);
ErrSuc OpenOutFileTask3(char *buffer, size_t bufSize);

size_t RunThroughBuffer(char *buffer, size_t bufSize);
void BufferToLinesFragmentation(char *buffer, Line *arrLines, size_t bufSize, size_t arrSize);
void GetLenghts(Line *arrLines, size_t arrSize);
void RunThroughBufferBack(char *buffer, size_t bufSize);

void ProgramDestroy(Info *programInfo, char *buffer, Line* arrLines);

int main(){
    
    Info programInfo = {}; 

    //printf("debug0\n");

    switch (OpenInFile("Onegin.txt", &(programInfo.fileInDescriptor), &(programInfo.fileSize))){
        case(RETURN_ERROR_FILEOPEN):
            printf("Error in input file opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FSTAT):
            printf("Error in input file opening in fuction fstat()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_TOO_LARGE_FILE_SIZE):
            printf("Input file is too large\n");
            return RETURN_ERROR;
        default:
            break;
    }    
    
    // TODO: Buffer -> buffer
    ///@note completed

    //printf("debug1\n");

    switch (ReadInFile(programInfo.fileInDescriptor, &programInfo.buffer, programInfo.fileSize)){
        case(RETURN_ERROR_FILEREAD):
            printf("Error in input file reading in fuction read()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_MEMORY_ALLOCATION):
            printf("Error in memory allocation\n");
            return RETURN_ERROR;
        default:
            break;
    }

    ///@note writing buffer before sorting
    int fileOutUnsortedDescriptor = open("onegin_out_unsorted.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOutUnsortedDescriptor, programInfo.buffer, programInfo.fileSize);

    //printf("debug2\n");

    ///@note changing '\r' and '\n' to '\0' and number of lines calculating
    programInfo.arrSize = RunThroughBuffer(programInfo.buffer, programInfo.fileSize);

    ///@note writing buffer in one line
    int fileOutInOneLineDescriptor = open("onegin_out_in_one_line.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fileOutInOneLineDescriptor, programInfo.buffer, programInfo.fileSize);

    // TODO: VLA - variable length array -- полное говно (budet crash), сделать calloc
    ///@note completed
    
    programInfo.arrLines = (Line *)calloc(programInfo.arrSize, sizeof(Line));

    //printf("debug3\n");

    ///@note fragmentation buffer to lines
    BufferToLinesFragmentation(programInfo.buffer, programInfo.arrLines, programInfo.fileSize, programInfo.arrSize);

    //printf("debug4\n");

    QuickSort(programInfo.arrLines, sizeof(Line), 0, programInfo.arrSize - 1, CompareStrOneginAscend);
    
    //printf("debug5\n");
    
    //qsort(programInfo.arrLines, programInfo.arrSize, sizeof(Line), CompareStrOneginDescend);

    switch (OpenOutFileTask1(programInfo.arrLines, programInfo.arrSize)){
        case(RETURN_ERROR_FILECREATE):
            printf("Error in input file creating or opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FILEWRITE_TASK1):
            printf("Error in input file writing in fuction write()\n");
            return RETURN_ERROR;
        default:
            break;
    }

    qsort(programInfo.arrLines, programInfo.arrSize, sizeof(Line), CompareStrOneginDescend);
        
    //printf("debug6\n");

    switch (OpenOutFileTask2(programInfo.arrLines, programInfo.arrSize)){
        case(RETURN_ERROR_FILEADD_TASK2):
            printf("Error in input file creating or opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FILEWRITE_TASK2):
            printf("Error in input file writing in fuction write()\n");
            return RETURN_ERROR;
        default:
            break;
    }

    switch (OpenOutFileTask3(programInfo.buffer, programInfo.fileSize)){
        case(RETURN_ERROR_FILEADD_TASK3):
            printf("Error in input file creating or opening in fuction open()\n");
            return RETURN_ERROR;
        case(RETURN_ERROR_FILEWRITE_TASK3):
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

    struct stat fileStat = {};
    // TODO: if style fix с пробелом везде сделай
    if (fstat(*fileInDescriptor, &fileStat) == -1) {return RETURN_ERROR_FSTAT;}

    *fileSize = fileStat.st_size;
    if (*fileSize >= (size_t)1<<32) {return RETURN_ERROR_TOO_LARGE_FILE_SIZE;};

    return RETURN_SUCCESS;
}

ErrSuc ReadInFile(int fileInDescriptor, char **buffer, size_t fileSize){

    char *bufferBeta = (char *)calloc(fileSize + 2, sizeof(char));
    if (bufferBeta == NULL) {return RETURN_ERROR_MEMORY_ALLOCATION;};

    //printf("bufBeta = %p\n", bufferBeta);

    *buffer = bufferBeta + 1;
    
    //printf("buf = %p\n", *buffer);

    if (read(fileInDescriptor, *buffer, fileSize) <= 0){
        close(fileInDescriptor);
        return RETURN_ERROR_FILEREAD;
    }
    

    close(fileInDescriptor);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFileTask1(Line *arrLines, size_t arrSize){
    assert(arrLines != NULL);

    //printf("OpenOutFile\n");


    FILE *fileOut /*_Descriptor*/ = fopen("onegin_out.txt", "w"/*O_CREAT | O_RDWR | O_TRUNC, 0666*/);
    if (fileOut /*_Descriptor*/ == NULL){
        fclose(fileOut /*_Descriptor*/);
        return RETURN_ERROR_FILECREATE;
    }

    fputs("===TASK1===\n\n", fileOut);
    
    for (size_t index = 0; index < arrSize; index++){
        char *strOut;
        //sprintf(strOut, "%s\n", arrLines[index].line);
        if (fprintf(fileOut, "%s\n", arrLines[index].line) <= 0){
            fclose(fileOut /*_Descriptor*/);
            return RETURN_ERROR_FILEWRITE_TASK1;
        }
    }

    fclose(fileOut /*_Descriptor*/);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFileTask2(Line *arrLines, size_t arrSize){
    assert(arrLines != NULL);

    //printf("OpenOutFile\n");


    FILE *fileOut /*_Descriptor*/ = fopen("onegin_out.txt", "a"/*O_CREAT | O_RDWR | O_TRUNC, 0666*/);

    if (fileOut /*_Descriptor*/ == NULL){
        fclose(fileOut /*_Descriptor*/);
        return RETURN_ERROR_FILEADD_TASK2;
    }

    fputs("\n===TASK2===\n\n", fileOut);

    for (size_t index = 0; index < arrSize; index++){
        char *strOut;
        //sprintf(strOut, "%s\n", arrLines[index].line);
        if (fprintf(fileOut, "%s\n", arrLines[index].line) <= 0){
            fclose(fileOut /*_Descriptor*/);
            return RETURN_ERROR_FILEWRITE_TASK2;
        }
    }
    fclose(fileOut /*_Descriptor*/);
    return RETURN_SUCCESS;
}

ErrSuc OpenOutFileTask3(char *buffer, size_t bufSize){
    assert(buffer != NULL);

    FILE *fileOut /*_Descriptor*/ = fopen("onegin_out.txt", "a"/*O_CREAT | O_RDWR | O_TRUNC, 0666*/);

    if (fileOut /*_Descriptor*/ == NULL){
        fclose(fileOut /*_Descriptor*/);
        return RETURN_ERROR_FILEADD_TASK3;
    }

    RunThroughBufferBack(buffer, bufSize);

    fputs("\n\n===TASK3===\n\n", fileOut);

    fwrite(buffer, sizeof(char), bufSize, fileOut);

    fclose(fileOut /*_Descriptor*/);
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

void RunThroughBufferBack(char *buffer, size_t bufSize){

    for (size_t index = 0; index < bufSize; index++){
        if (buffer[index] == '\0'){
            buffer[index] = '\n';
        }
    }
}



void BufferToLinesFragmentation(char *buffer, Line *arrLines, size_t bufSize, size_t arrSize){
    assert(buffer != NULL);
    assert(arrLines != NULL);

    // printf("buffer = [%s]\n", buffer);
    // printf("arrLines ptr = %p\n", arrLines);
    // printf("bufSize = %llu\n", bufSize);

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
    //printf("hey\n");
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
                arrLines[index].len = arrLines[index + 1].line - arrLines[index].line - 1;
                //TODO change strlen to ptr + 1 - ptr
                ///@note completed
            }
            //printf("len = %d\n", arrLines[index].len);
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