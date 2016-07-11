#ifndef TEMPLATE_ARRAY_H
#define TEMPLATE_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/cclasses/cclasses.h"
#include "lib/cexception/CException.h"
#include "error_codes.h"
#include <stdlib.h>


/* A batter way of specific typename */
#define Array(T) Array_##T


/* Minimal capacity */
#define MIN_CAPACITY 16
#define FACTOR 2


/* This macros generates defenition of a specific type of Array(T) */
#define TemplateArray(T)                                                        \
                                                                                \
cclass_(Array_##T) {                                                            \
    /* fields */                                                                \
    size_t  _size;                                                              \
    size_t  _capacity;                                                          \
    T*      _array;                                                             \
                                                                                \
    /* methods */                                                               \
    method_def_(void,   push_back,      Array(T)) with_(T value);               \
    method_def_(T,      pop_back,       Array(T)) without_args;                 \
    method_def_(void,   reserve,        Array(T)) without_args;                 \
    method_def_(void,   shrink,         Array(T)) without_args;                 \
    method_def_(_Bool,  is_empty,       Array(T)) without_args;                 \
    method_def_(_Bool,  is_valid_index, Array(T)) with_(int index);             \
    method_def_(T,      at,             Array(T)) with_(int index);             \
    method_def_(void,   set,            Array(T)) with_(int index, T value);    \
};                                                                              \
                                                                                \
constructor_(Array(T))();                                                       \
destructor_(Array(T));


/* This macros generates a code for methods of Array(T) */
#define TemplateArrayImplementation(T)                                          \
                                                                                \
method_body_(void, push_back, Array(T)) with_(T value) {                        \
    if (self->_size == self->_capacity) {                                       \
        self->reserve(self);                                                    \
    }                                                                           \
                                                                                \
    self->_array[self->_size++] = value;                                        \
}                                                                               \
                                                                                \
                                                                                \
method_body_(T, pop_back, Array(T)) without_args {                              \
    if (self->is_empty(self)) {                                                 \
        Throw(EMPTY_ARRAY);                                                     \
    }                                                                           \
                                                                                \
    return self->_array[self->_size-- - 1];                                     \
}                                                                               \
                                                                                \
                                                                                \
method_body_(void, reserve, Array(T)) without_args {                            \
    self->_capacity *= FACTOR;                                                  \
    T* new_array = (T*) calloc(self->_capacity, sizeof(T));                     \
                                                                                \
    for (unsigned int i = 0; i < self->_size; ++i) {                            \
        new_array[i] = self->_array[i];                                         \
    }                                                                           \
                                                                                \
    free(self->_array);                                                         \
    self->_array = new_array;                                                   \
    new_array = NULL;                                                           \
}                                                                               \
                                                                                \
                                                                                \
method_body_(void, shrink, Array(T)) without_args {                             \
    self->_capacity = self->_size > MIN_CAPACITY ? self->_size : MIN_CAPACITY;  \
    T* new_array = (T*) calloc(self->_capacity, sizeof(T));                     \
                                                                                \
    for (unsigned int i = 0; i < self->_size; ++i) {                            \
        new_array[i] = self->_array[i];                                         \
    }                                                                           \
                                                                                \
    free(self->_array);                                                         \
    self->_array = new_array;                                                   \
    new_array = NULL;                                                           \
}                                                                               \
                                                                                \
                                                                                \
method_body_(_Bool, is_empty, Array(T)) without_args {                          \
    return self->_size == 0;                                                    \
}                                                                               \
                                                                                \
                                                                                \
method_body_(_Bool, is_valid_index, Array(T)) with_(int index) {                \
    index = index >= 0 ? index : (int) self->_size + index;                     \
                                                                                \
    if (index >= 0 && index < (int) self->_size) {                              \
        return 1;                                                               \
    }                                                                           \
                                                                                \
    return 0;                                                                   \
}                                                                               \
                                                                                \
                                                                                \
method_body_(T, at, Array(T)) with_(int index) {                                \
    index = index >= 0 ? index : (int) self->_size + index;                     \
                                                                                \
    if (index < 0 || index >= (int) self->_size) {                              \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    return self->_array[index];                                                 \
}                                                                               \
                                                                                \
                                                                                \
method_body_(void, set, Array(T)) with_(int index, T value)                     \
{                                                                               \
    index = index >= 0 ? index : (int) self->_size + index;                     \
                                                                                \
    if (index < 0 || index >= (int) self->_size) {                              \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    self->_array[index] = value;                                                \
}                                                                               \
                                                                                \
                                                                                \
constructor_(Array(T))() {                                                      \
    new_self_(Array_##T);                                                       \
                                                                                \
    self->_size = 0;                                                            \
    self->_capacity = MIN_CAPACITY;                                             \
    self->_array = (T*) calloc(self->_capacity, sizeof(T));                     \
                                                                                \
    init_method_(push_back);                                                    \
    init_method_(pop_back);                                                     \
    init_method_(reserve);                                                      \
    init_method_(shrink);                                                       \
    init_method_(is_empty);                                                     \
    init_method_(is_valid_index);                                               \
    init_method_(at);                                                           \
    init_method_(set);                                                          \
                                                                                \
    return self;                                                                \
}                                                                               \
                                                                                \
                                                                                \
destructor_(Array(T)) {                                                         \
    free(self->_array);                                                         \
    free(self);                                                                 \
}

#ifdef __cplusplus
}
#endif

#endif // TEMPLATE_ARRAY_H