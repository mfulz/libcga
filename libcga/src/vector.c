#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

int __c_vec_grow(VECTOR* _vector)
{
    void* new_data = NULL;
    new_data =
        realloc(_vector->data, _vector->elem_size * (_vector->size + _vector->grow_rate));
    if (!new_data)
    {
        return C_VEC_EMALLOC;
    }

    _vector->capacity += _vector->grow_rate;
    _vector->data = new_data;

    return C_VEC_SUCCESS;
}

int c_vector_create(size_t _elem_size, size_t _init_capacity, size_t _grow_rate,
                    c_vector_free* _free, VECTOR** _vector)
{
    *_vector = NULL;
    *_vector = malloc(sizeof(VECTOR));
    if (!*_vector)
    {
        return C_VEC_EMALLOC;
    }

    (*_vector)->elem_size = _elem_size;
    (*_vector)->capacity  = _init_capacity;
    (*_vector)->grow_rate = _grow_rate;
    (*_vector)->size      = 0;
    (*_vector)->free      = _free;
    (*_vector)->data      = NULL;
    (*_vector)->data      = malloc((*_vector)->capacity * (*_vector)->elem_size);
    if (!(*_vector)->data)
    {
        free(*_vector);
        return C_VEC_EMALLOC;
    }

    return C_VEC_SUCCESS;
}

void c_vector_destroy(VECTOR* _vector)
{
    if (!_vector)
    {
        return;
    }

    if (_vector->free)
    {
        int end = _vector->size;
        for (int i = 0; i < end; i++)
        {
            _vector->free(c_vector_at(i, _vector));
        }
    }

    if (_vector->data)
    {
        free(_vector->data);
    }

    free(_vector);
}

void* c_vector_begin(VECTOR* _vector)
{
    return _vector->data;
}

void* c_vector_end(VECTOR* _vector)
{
    return _vector->data + (_vector->elem_size * _vector->size);
}

void* c_vector_next(void* _it, VECTOR* _vector)
{
    return _it + _vector->elem_size;
}

size_t c_vector_size(VECTOR* _vector)
{
    return _vector->size;
}

size_t c_vector_capacity(VECTOR* _vector)
{
    return _vector->capacity;
}

int c_vector_empty(VECTOR* _vector)
{
    return _vector->size == 0;
}

void* c_vector_at(size_t _index, VECTOR* _vector)
{
    if (_index < 0 || _index > (_vector->size - 1))
    {
        return NULL;
    }

    return (_vector->data + (_vector->elem_size * _index));
}

void* c_vector_front(VECTOR* _vector)
{
    return c_vector_at(0, _vector);
}

void* c_vector_back(VECTOR* _vector)
{
    return c_vector_at(_vector->size - 1, _vector);
}

void* c_vector_data(VECTOR* _vector)
{
    return _vector->data;
}

int c_vector_push_back(void* _elem, VECTOR* _vector)
{
    int ret = 0;

    if (_vector->size == _vector->capacity)
    {
        if ((ret = __c_vec_grow(_vector)) != C_VEC_SUCCESS)
        {
            return ret;
        }
    }

    memcpy(_vector->data + (_vector->size * _vector->elem_size), _elem,
           _vector->elem_size);
    _vector->size++;

    return C_VEC_SUCCESS;
}

int c_vector_pop_back(VECTOR* _vector)
{
    if (_vector->size == 0)
    {
        return C_VEC_EEMPTY;
    }

    if (_vector->free)
    {
        _vector->free(c_vector_at(_vector->size - 1, _vector));
    }
    _vector->size--;

    return C_VEC_SUCCESS;
}

int c_vector_insert(const void* _elem, size_t _index, VECTOR* _vector)
{
    int ret = 0;

    if (_index < 0 || _index > (_vector->size - 1))
    {
        return C_VEC_EINDEX;
    }

    if (_vector->size == _vector->capacity)
    {
        if ((ret = __c_vec_grow(_vector)) != C_VEC_SUCCESS)
        {
            return ret;
        }
    }

    if (!memmove(c_vector_at(_index + 1, _vector), c_vector_at(_index, _vector),
                 _vector->elem_size * (_vector->size - _index)))
    {
        return C_VEC_EERROR;
    }

    if (!memcpy(c_vector_at(_index, _vector), _elem, _vector->elem_size))
    {
        return C_VEC_EERROR;
    }
    _vector->size++;

    return C_VEC_SUCCESS;
}

void c_vector_clear(VECTOR* _vector)
{
    if (_vector->free)
    {
        int end = _vector->size;
        for (int i = 0; i < end; i++)
        {
            _vector->free(c_vector_at(i, _vector));
        }
    }

    _vector->size = 0;
}
