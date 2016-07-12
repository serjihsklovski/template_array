#include <stdio.h>
#include "test/arrray_double.h"


int main() {
    printf("size of 'Array_double': %d bytes.\n", sizeof(Array_double));
    printf("size of 'struct _Array_double_t': %d bytes.\n\n", sizeof(struct _Array_double_t));


    /* creating array */
    Array(double) arr = new_Array_double(MIN_CAPACITY);     // create Array_double object

    double var = 0.1;

    printf("new array: size=%d, capacity=%d\n\n", arr->_size, arr->_capacity);


    /* pushing elements */
    printf("pushing elements...\n");

    for (int i = 0; i < 20; ++i, var *= 2.7) {
        arr->push_back(arr, var);
        printf("    number %lf was pushed into arr\n", var);
    }

    printf("\narray before shinking: size=%d, capacity=%d\n", arr->_size, arr->_capacity);
    arr->shrink(arr);
    printf("array after shrinking: size=%d, capacity=%d\n\n", arr->_size, arr->_capacity);

    for (int i = 0; i < (int) arr->_size; ++i) {
        printf("%2i: %lf\n", i, arr->at(arr, i));
    }


    /* exceptions */
    CEXCEPTION_T e;

    Try {
        double x = arr->at(arr, 1000);  // 1000 - unreal index
        printf("x = %lf\n", x);         // it won't execute
    } Catch (e) {
        switch (e) {
            case INDEX_IS_OUT_OF_RANGE:
                printf("bad index, dude!\n\n");
        }
    }


    /* popping elements */
    printf("popping elements...\n");

    while (!arr->is_empty(arr)) {
        printf("    %lf\n", arr->pop_back(arr));
    }

    printf("\narray before shrinking: size=%d, capacity=%d\n", arr->_size, arr->_capacity);
    arr->shrink(arr);
    printf("array after shrinking: size=%d, capacity=%d\n\n", arr->_size, arr->_capacity);


    /* changing elements in arrays */
    arr->push_back(arr, 12.34);
    arr->push_back(arr, -5.678);
    arr->push_back(arr, 0.009);

    for (int i = 0; i < (int) arr->_size; ++i) {
        printf("%2i: %lf\n", i, arr->at(arr, i));
    }

    printf("\n");

    arr->set(arr, -1, 111.111);             // change last element
    arr->set(arr, 1, 222.222);              // change second element
    arr->set(arr, 0, arr->at(arr, -1));     // first = last

    for (int i = 0; i < (int) arr->_size; ++i) {
        printf("%2i: %lf\n", i, arr->at(arr, i));
    }

    delete_(Array_double)(arr);

    return 0;
}
