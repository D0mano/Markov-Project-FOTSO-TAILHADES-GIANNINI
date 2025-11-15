#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *getID(int num) {
    if (num < 1) {
        return NULL;
    }

    // Calculate the length needed for the result
    int len = 0;
    int temp = num;
    while (temp > 0) {
        len++;
        temp = (temp - 1) / 26;
    }

    // Allocate memory for the result (+1 for null terminator)
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    // Fill the string from right to left
    result[len] = '\0';
    temp = num;

    for (int i = len - 1; i >= 0; i--) {
        temp--;
        result[i] = 'A' + (temp % 26);
        temp /= 26;
    }

    return result;
}

int min(int a,int b) {
    return a < b ? a : b;
}

