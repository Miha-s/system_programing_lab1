struct StringsVector
{
    int real_size;
    int size;
    wchar_t **strings;
};

typedef struct StringsVector StringsVector_t;

void clear_vector(StringsVector_t *vector);
void add_unique_to_vector(StringsVector_t *vector, wchar_t *word);
StringsVector_t *create_vector();
void free_vector(StringsVector_t *vector);