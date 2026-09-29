# STRINGS SORTER

Hello, GitHub! Here is my Strings Sorter!

This repository contains the code for a program that sorts strings in text files. Program can sort strings by them beginnings and by they ends.

## How it works?

1. Program takes file name from console. Program don't crash, if you don't enter file name. Default file name is "onegin.txt" - text file of "Onegin" by Alexander Pushkin.
2. In the begining program creates a struct called env (Environment), that contains all information about program.
3. Then program allocates buffer, reads text from file and puts it to buffer.
4. Then program fragmentates buffer to lines, puts them in allocated array and sorts them.
5. Program has 3 modes of sorting:
    1. Sorting by begining of the strings **(mode 1)**
    2. Sorting by ends of the strings **(mode 2)**
    3. Output unsorted text **(mode 0)**
6. Then program output sorted strings in file "output.txt"
7. In the the end program destroys the struct by filling it poison values, closes files and frees allocated memory


## How to start the program?

1. *Ctrl + [ ` ]* || to open console
2. *g++ sorting.cpp -o [executable file name]* || to compilate project
3. *.\\[executable file name] "FileToSort.txt" [ modes ]* || to sort "FileToSort.txt" with modes:
    1. *mode 0* || output unsorted text
    2. *mode 1* || output sorted text by strings' beginnings
    3. *mode 2* || output sorrted text by strings' ends

## Features:

<details>
<summary>Includes:</summary>
#include <stdio.h>\
#include <stdlib.h>\
#include <string.h>\
#include <sys/stat.h>\
#include <fcntl.h>\
#include <errno.h>\
#include <assert.h>
</details>