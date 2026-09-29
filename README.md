# SQUARE EQUATIONS SOLVER

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

1. Ctrl+` || to open console
2. *g++ main.cpp -o "exe file name"* || to compilate program
3. *.\\"exe file name" **-t/--test*** || to start test mode
4. *.\\"exe file name" **-i/--interactive*** || to start interactive mode
5. *.\\"exe file name" **-c/--coefficient*** "a-coefficient value" "b-coefficient value" "c-coefficient value"* || to start console input mode

There is nothing to care, i provide for incorrect input from the user. The input repeats, until the input won't be correct.

The program works with real numbers, but **Solver** provides for the case of negative discriminant, and is able to calculate complex roots.

Comparison of double numbers is performed with accuracy **EPS = 1 * 10^-6**.


<details>
<summary>Includes:</summary>

<stdio.h>\
<stdlib.h>\
<math.h>\
<string.h>

</details>