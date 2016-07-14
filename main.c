#include <stdio.h>
#include "test/array_double.h"
#include "test/array_int.h"


int main() {
    printf("size of 'Array_double': %d bytes.\n", sizeof(Array_double));
    printf("size of 'struct _Array_double_t': %d bytes.\n\n", sizeof(struct _Array_double_t));
    printf("size of 'Array_int': %d bytes.\n", sizeof(Array_int));
    printf("size of 'struct _Array_int_t': %d bytes.\n\n", sizeof(struct _Array_int_t));


    /* creating array */
    Array(double) arr = new_Array_double(MIN_CAPACITY);     // create Array_double object
    Array(int) vec = new_Array_int(MIN_CAPACITY);           // create Array_int object

    double var = 0.1;

    printf("arr: size=%d, capacity=%d\n", arr->_size, arr->_capacity);
    printf("vec: size=%d, capacity=%d\n\n", vec->_size, vec->_capacity);


    /* pushing elements */
    printf("pushing elements...\n");

    for (int i = 0; i < 20; ++i, var *= 2.7) {
        arr->push_back(arr, var);
        printf("    number %lf was pushed into arr\n", var);
    }
    puts("");

    for (int i = 0; i < 17; ++i) {
        vec->push_back(vec, i * i);
        printf("    number %d was pushed into vec\n", vec->at(vec, -1));
    }
    puts("");

    printf("arr before shinking: size=%d, capacity=%d\n", arr->_size, arr->_capacity);
    printf("vec before shinking: size=%d, capacity=%d\n", vec->_size, vec->_capacity);

    arr->shrink(arr);
    vec->shrink(vec);

    printf("arr after shrinking: size=%d, capacity=%d\n", arr->_size, arr->_capacity);
    printf("vec after shrinking: size=%d, capacity=%d\n\n", vec->_size, vec->_capacity);

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

    /* insertion */
    arr->insert(arr, 1, 333.333);           // [111.111, 333.333, 222.222, 111.111]
    arr->pop(arr, 2);                       // [111.111, 333.333, 111.111]

    /* swapping */
    arr->swap(arr, 0, 1);                   // [333.333, 111.111, 111.111]

    for (int i = 0; i < (int) arr->_size; ++i) {
        printf("%2i: %lf\n", i, arr->at(arr, i));
    }
    puts("");


    /* copying */
    Array(int) vec2 = vec->copy(vec);

    delete_(Array_double)(arr);
    delete_(Array_int)(vec);

    for (int i = 0; i < (int) vec2->_size; ++i) {
        printf("%2d: %d\n", i, vec2->at(vec2, i));
    }

    delete_(Array_int)(vec2);

    return 0;
}
