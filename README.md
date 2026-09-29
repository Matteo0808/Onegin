# STRINGS SORTER

Hello, GitHub! Here is my Strings Sorter!

This repository contains the code for a program that sorts strings in text files. Program can sort strings by them beginnings and by they endings.

## How it works?

1. Program takes file name from console. Program don't crash, if you don't enter file name. Default file name is "onegin.txt" - text file of "Onegin" by Alexander Pushkin.
2. In the begining program creates a struct called env (Environment), that contains all information about program.
3. Then program allocates buffer, reads text from file and puts it to buffer.
4. Then program fragmentates buffer to lines, puts them in allocated array and sorts them.
5. Program has 4 modes of sorting:
    1. Output unsorted text **(mode --unsorted or -u)**
    2. Sorting by begining of the strings **(mode --beginning or -b)**
    3. Sorting by endings of the strings **(mode --ending or -e)** 
    4. All modes on **(mode --all or -a)**
    5. Only sorting modes on **(mode --sortsonly or -s)**
6. Then program output sorted strings in file "output.txt"
7. In the the end program destroys the struct by filling it poison values, closes files and frees allocated memory


## How to start the program?

1. *Ctrl + [ ` ]* || to open console
2. *g++ sorting.cpp -o [executable file name]* || to compilate project
3. *.\\[executable file name] "FileToSort.txt" [ mode]* || to sort "FileToSort.txt" with modes:
    1. *mode --unsorted or -u* || output unsorted text
    2. *mode --beginning or -b* || output sorted text by strings' beginnings
    3. *mode --ending or -e* || output sorrted text by strings' endings
    4. *mode --all or -a* || output all modes
    5. *mode --sortsonly or -s* || output sorts only modes
4. *default file name is onegin.txt and default mode is --beginning*

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