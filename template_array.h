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
#define MIN_CAPACITY 16u
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
    method_def_(void,   push_back,  Array(T)) with_(T value);                   \
    method_def_(T,      pop_back,   Array(T)) without_args;                     \
    method_def_(void,   reserve,    Array(T)) without_args;                     \
    method_def_(void,   shrink,     Array(T)) without_args;                     \
    method_def_(_Bool,  is_empty,   Array(T)) without_args;                     \
    method_def_(_Bool,  has_index,  Array(T)) with_(int index);                 \
    method_def_(T,      at,         Array(T)) with_(int index);                 \
    method_def_(void,   set,        Array(T)) with_(int index, T value);        \
    method_def_(void,   insert,     Array(T)) with_(int index, T value);        \
    method_def_(T,      pop,        Array(T)) with_(int index);                 \
    method_def_(void,   clear,      Array(T)) without_args;                     \
    method_def_(Array(T),   copy,   Array(T)) without_args;                     \
    method_def_(void,   swap,       Array(T)) with_(int index_1, int index_2);  \
};                                                                              \
                                                                                \
constructor_(Array(T))(size_t capacity);                                        \
destructor_(Array(T));


/* This macros generates a code for methods of Array(T) */
#define TemplateArrayImplementation(T)                                          \
                                                                                \
static int _get_abs_index(int relative_index, size_t size) {                    \
    return relative_index >= 0 ? relative_index : (int) size + relative_index;  \
}                                                                               \
                                                                                \
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
} throws_(EMPTY_ARRAY)                                                          \
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
method_body_(_Bool, has_index, Array(T)) with_(int index) {                     \
    index = _get_abs_index(index, self->_size);                                 \
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
    if (!self->has_index(self, index)) {                                        \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    index = _get_abs_index(index, self->_size);                                 \
                                                                                \
    return self->_array[index];                                                 \
} throws_(INDEX_IS_OUT_OF_RANGE)                                                \
                                                                                \
                                                                                \
method_body_(void, set, Array(T)) with_(int index, T value) {                   \
    if (!self->has_index(self, index)) {                                        \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    index = _get_abs_index(index, self->_size);                                 \
                                                                                \
    self->_array[index] = value;                                                \
} throws_(INDEX_IS_OUT_OF_RANGE)                                                \
                                                                                \
                                                                                \
method_body_(void, insert, Array(T)) with_(int index, T value) {                \
    if (self->has_index(self, index)) {                                         \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    index = _get_abs_index(index, self->_size);                                 \
                                                                                \
    if (self->_size + 1u >= self->_capacity) {                                  \
        self->reserve(self);                                                    \
    }                                                                           \
                                                                                \
    T temp;                                                                     \
                                                                                \
    for (unsigned int i = index; i < self->_size; ++i) {                        \
        temp = self->_array[i];                                                 \
        self->_array[i] = value;                                                \
        value = temp;                                                           \
    }                                                                           \
                                                                                \
    self->_array[self->_size] = temp;                                           \
    ++self->_size;                                                              \
} throws_(INDEX_IS_OUT_OF_RANGE)                                                \
                                                                                \
                                                                                \
method_body_(T, pop, Array(T)) with_(int index) {                               \
    if (!self->has_index(self, index)) {                                        \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    index = _get_abs_index(index, self->_size);                                 \
                                                                                \
    T value = self->_array[index];                                              \
                                                                                \
    for (unsigned int i = index; i < self->_size - 1; ++i) {                    \
        self->_array[i] = self->_array[i + 1];                                  \
    }                                                                           \
                                                                                \
    --self->_size;                                                              \
    return value;                                                               \
} throws_(INDEX_IS_OUT_OF_RANGE)                                                \
                                                                                \
                                                                                \
method_body_(void, clear, Array(T)) without_args {                              \
    self->_size = 0;                                                            \
}                                                                               \
                                                                                \
                                                                                \
method_body_(Array(T), copy, Array(T)) without_args {                           \
    Array(T) new_array = new_(Array_##T)(self->_capacity);                      \
                                                                                \
    new_array->_size = self->_size;                                             \
                                                                                \
    for (unsigned int i = 0; i < self->_size; ++i) {                            \
        new_array->_array[i] = self->_array[i];                                 \
    }                                                                           \
                                                                                \
    return new_array;                                                           \
}                                                                               \
                                                                                \
                                                                                \
method_body_(void, swap, Array(T)) with_(int index_1, int index_2) {            \
    index_1 = _get_abs_index(index_1, self->_size);                             \
    index_2 = _get_abs_index(index_2, self->_size);                             \
                                                                                \
    if (!self->has_index(self, index_1) ||                                      \
        !self->has_index(self, index_2))                                        \
    {                                                                           \
        Throw(INDEX_IS_OUT_OF_RANGE);                                           \
    }                                                                           \
                                                                                \
    if (index_1 == index_2) {                                                   \
        return;                                                                 \
    } else {                                                                    \
        T temp = self->_array[index_1];                                         \
        self->_array[index_1] = self->_array[index_2];                          \
        self->_array[index_2] = temp;                                           \
    }                                                                           \
} throws_(INDEX_IS_OUT_OF_RANGE)                                                \
                                                                                \
                                                                                \
constructor_(Array(T))(size_t capacity) {                                       \
    new_self_(Array_##T);                                                       \
                                                                                \
    self->_size = 0;                                                            \
    self->_capacity = capacity < MIN_CAPACITY ? MIN_CAPACITY : capacity;        \
    self->_array = (T*) calloc(self->_capacity, sizeof(T));                     \
                                                                                \
    init_method_(push_back);                                                    \
    init_method_(pop_back);                                                     \
    init_method_(reserve);                                                      \
    init_method_(shrink);                                                       \
    init_method_(is_empty);                                                     \
    init_method_(has_index);                                                    \
    init_method_(at);                                                           \
    init_method_(set);                                                          \
    init_method_(insert);                                                       \
    init_method_(pop);                                                          \
    init_method_(clear);                                                        \
    init_method_(copy);                                                         \
    init_method_(swap);                                                         \
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
