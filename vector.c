#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "vector.h"


StringsVector_t *create_vector()
{
    static const int initial_vector_size = 10;
    StringsVector_t *tmp_vector = malloc(sizeof(StringsVector_t));
    tmp_vector->real_size = initial_vector_size;
    tmp_vector->size = 0;
    tmp_vector->strings = malloc(sizeof(wchar_t *) * initial_vector_size);

    return tmp_vector;
}

void clear_vector(StringsVector_t *vector) {
    for (int i = 0; i < vector->size; i++)
    {
        free(vector->strings[i]);
    }

    vector->size = 0;
}

void double_vector(StringsVector_t *vector) {
    const int new_size = vector->real_size*2;
    wchar_t **new_strings = malloc(sizeof(wchar_t*) * new_size);
    for (int i = 0; i < vector->size; i++)
    {
        new_strings[i] = vector->strings[i];
    }
    
    wchar_t **temp = vector->strings;
    vector->strings = new_strings;
    free(temp);
}


void add_unique_to_vector(StringsVector_t *vector, wchar_t *word) {
    for (int i = 0; i < vector->size; i++)
    {
        if(!wcscmp(vector->strings[i], word)) {
            return ;
        }
    }

    if(vector->size == vector->real_size) {
        double_vector(vector);
    }

    vector->strings[vector->size] = word;
    vector->size++;
}

void free_vector(StringsVector_t *vector) {
    clear_vector(vector);
    free(vector->strings);
    free(vector);
}