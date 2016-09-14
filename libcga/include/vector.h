/** \file vector.h
 * Header file for STL like vector implementation
 */

#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdlib.h>

#define C_VEC_SUCCESS 0
#define C_VEC_SIZE_MISMATCH 1
#define C_VEC_EMALLOC 2
#define C_VEC_EEMPTY 3
#define C_VEC_EINDEX 4
#define C_VEC_EERROR 5

typedef void(c_vector_free)(void*);

typedef struct _c_vector
{
    size_t elem_size;
    size_t size;
    size_t capacity;
    size_t grow_rate;
    void* data;
    c_vector_free* free;
} VECTOR;

// constructor and destructor
int c_vector_create(size_t _elem_size, size_t _init_capacity, size_t _grow_rate,
                    c_vector_free* _free, VECTOR** _vector);
void c_vector_destroy(VECTOR* _vector);

// iterators
void* c_vector_begin(VECTOR* _vector);
void* c_vector_end(VECTOR* _vector);
void* c_vector_next(void* _it, VECTOR* _vector);

// capacity
size_t c_vector_size(VECTOR* _vector);
size_t c_vector_capacity(VECTOR* _vector);
int c_vector_empty(VECTOR* _vector);

// access
void* c_vector_at(size_t _index, VECTOR* _vector);
void* c_vector_front(VECTOR* _vector);
void* c_vector_back(VECTOR* _vector);
void* c_vector_data(VECTOR* _vector);

// modifiers
int c_vector_push_back(void* _elem, VECTOR* _vector);
int c_vector_pop_back(VECTOR* _vector);
int c_vector_insert(const void* _elem, size_t _index, VECTOR* _vector);
void c_vector_clear(VECTOR* _vector);

#endif /* ifndef __VECTOR_H */
