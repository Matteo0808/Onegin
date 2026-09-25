#ifndef COMPARATORS_H
#define COMPORATORS_H

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

bool IsEqual(const double number1, const double number2);

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

bool IsEqual(const double number1, const double number2){

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

    const char *str1 = *((const char **)elem1);
    const char *str2 = *((const char **)elem2);

    assert(str1 != NULL);
    assert(str2 != NULL);

    printf("^hui\n");

    while (!isalpha(*str1)) { str1++;}
    printf("huistr1\n");
    while (!isalpha(*str2)){ str2++;}
    printf("huistr2\n");

    int index = 0;

    while(tolower(str1[index]) == tolower(str2[index])){
        if(str1 == 0){
            return 0;
        }
        index++;
        printf("^^hui\n");
    }
    return tolower(str1[index]) - tolower(str2[index]);
}

#endif





