#ifndef COMPARATORS_H
#define COMPARATORS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define EPSYLON 1e-9

int CompareIntAscend(const void* elem1, const void* elem2);
int CompareIntDescend(const void* elem1, const void* elem2);
int CompareStrAscend(const void* elem1, const void* elem2);
int CompareStrDescend(const void* elem1, const void* elem2);
int CompareDoubAscend(const void* elem1, const void* elem2);
int CompareDoubDescend(const void* elem1, const void* elem2);
int CompareChrAscend(const void* elem1, const void* elem2);
int CompareChrDescend(const void* elem1, const void* elem2);
int CompareStrOneginAscend(const void *elem1, const void *elem2);

int IsEqual(const double number1, const double number2);

int CompareIntAscend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const int val1 = *(const int *)elem1;
    const int val2 = *(const int *)elem2;
    if (val1 > val2) {return 1;}
    if (val1 < val2) {return -1;}
    else {return 0;}
}

int CompareIntDescend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const int val1 = *(const int *)elem1;
    const int val2 = *(const int *)elem2;
    if (val1 < val2) {return 1;}
    if (val1 > val2) {return -1;}
    else {return 0;}
}

int CompareStrAscend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const char **str1 = (const char **)elem1;
    const char **str2 = (const char **)elem2;
    int compare = strcmp(*str1, *str2);
    if(compare > 0) {return 1;}
    if(compare < 0) {return -1;}
    else {return 0;}
}

int CompareStrDescend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const char **str1 = (const char **)elem1;
    const char **str2 = (const char **)elem2;
    int compare = strcmp(*str1, *str2);
    if(compare < 0) {return 1;}
    if(compare > 0) {return -1;}
    else {return 0;}
}

int CompareDoubAscend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const double val1 = *(const double *)elem1;
    const double val2 = *(const double *)elem2;
    if (IsEqual(val1, val2) > 0) {return 1;}
    if (IsEqual(val1, val2) < 0) {return -1;}
    else {return 0;}
}

int CompareDoubDescend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const double val1 = *(const double *)elem1;
    const double val2 = *(const double *)elem2;
    if (IsEqual(val1, val2) < 0) {return 1;}
    if (IsEqual(val1, val2) > 0) {return -1;}
    else {return 0;}
}

int IsEqual(const double number1, const double number2){

    double delta = number1 - number2;
    if (delta > EPSYLON){
        return 1;
    }
    if (delta < -EPSYLON){
        return -1;
    }
    else{
        return 0;
    }
}

int CompareChrAscend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const char val1 = *(const char *)elem1;
    const char val2 = *(const char *)elem2;
    if (val1 > val2) {return 1;}
    if (val1 < val2) {return -1;}
    else {return 0;}
}

int CompareChrDescend(const void* elem1, const void* elem2){
    assert(elem1 != 0);
    assert(elem2 != 0);

    const int val1 = *(const char *)elem1;
    const int val2 = *(const char *)elem2;
    if (val1 > val2) {return 1;}
    if (val1 < val2) {return -1;}
    else {return 0;}
}


int CompareStrOneginAscend(const void *elem1, const void *elem2){
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    const char *str1 = *((const char * const *)elem1);
    const char *str2 = *((const char * const *)elem2);

    printf("str1 = [%s]\n", str1);
    printf("str2 = [%s]\n", str2);

    // const char *str1 =  ((Line *)elem1)->line;
    // const char *str2 =  ((Line *)elem2)->line;

    assert(str1 != NULL);
    assert(str2 != NULL);


    //printf("^hui\n");

    while (*str1 && !isalpha(*str1)) { str1++;}
    while (*str2 && !isalpha(*str2)){ str2++;}

    while (*str1 && *str2) {
        int c1 = tolower((unsigned char)*str1);
        int c2 = tolower((unsigned char)*str2);
        if (c1 != c2) return c1 - c2;
        str1++; str2++;
    }
    return 0;
}
//     int index = 0;

//     while(tolower(str1[index]) == tolower(str2[index])){
//         if(str1[index] == 0){
//             return 0;
//         }
//         index++;
//     }

//     printf("HUUIIIIII");
//     return tolower(str1[index]) - tolower(str2[index]);
// }

#endif





