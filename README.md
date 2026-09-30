# STRINGS SORTER

Hello, GitHub! Here is my Strings Sorter!

This repository contains the code for a program that sorts strings in the text files. Program can sort strings by their beginnings and by their endings.

## How it works?

1. Program takes file name from the console. Program doesn't crash, if you don't enter file name. Default file name is "onegin.txt" - text file of "Onegin" by Alexander Pushkin.
2. First, program creates a struct called env (Environment), that contains all information about program.
3. Then program allocates buffer, reads text from file and puts it to buffer.
4. Then program separates buffer to lines, puts them in allocated array and sorts them.
5. Program has 5 modes of sorting:
    1. Output unsorted text
    2. Sorting by begining of the strings
    3. Sorting by endings of the strings
    4. All modes on
    5. Only sorting modes on
6. Then program output sorted strings in file "output.txt".
7. Finally, program destroys the struct by filling it poison values, closes files and frees allocated memory


## How to start the program in VSCode?
**This is tutorial how to open program in Visual Studio Code**
**Program uses MinGW compiler**

1. *Ctrl + [ ` ]* || to open console in vscode
2. *g++ sorting.cpp -o [executable file name]* || to compile project
3. *.\\[executable file name] ["FileToSort.txt"] [ mode]* || to sort "FileToSort.txt" with modes:
    1. *mode --unsorted or -u* || output unsorted text
    2. *mode --beginning or -b* || output sorted text by strings' beginnings
    3. *mode --ending or -e* || output sorrted text by strings' endings
    4. *mode --all or -a* || output all modes
    5. *mode --sortsonly or -s* || output sorts only modes
4. *default file name is onegin.txt and default mode is --beginning*

## Features:

<details>
<summary>Includes:</summary>

<stdio.h>\
<stdlib.h>\
<string.h>\
<sys/stat.h>\
<fcntl.h>\
<errno.h>\
<assert.h>

</details>