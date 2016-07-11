#include <stdio.h>
#include "test/arrray_double.h"


int main() {
    printf("size of 'Array_double': %d bytes.\n", sizeof(Array_double));
    printf("size of 'struct _Array_double_t': %d bytes.\n\n", sizeof(struct _Array_double_t));

    Array(double) arr = new_Array_double();     // create Array_double object

    double var = 0.1;

    printf("new array: size=%d, capacity=%d\n\n", arr->_size, arr->_capacity);
    printf("pushing elements...\n");

    for (int i = 0; i < 20; ++i, var *= 2.7) {
        arr->push_back(arr, var);
        printf("    number %lf was pushed into arr\n", var);
    }

    printf("\narray: size=%d, capacity=%d\n\n", arr->_size, arr->_capacity);

    for (int i = 0; i < (int) arr->_size; ++i) {
        printf("%2i: %lf\n", i, arr->at(arr, i));
    }

    delete_(Array_double)(arr);

    return 0;
}
