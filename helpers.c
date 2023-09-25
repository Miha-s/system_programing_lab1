#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <wchar.h>
#include <wctype.h>
#include "helpers.h"

int is_character(wchar_t c)
{
    return iswalpha(c);
}

int is_vowel(wchar_t c)
{
    switch (c)
    {
    case L'а':
    case L'о':
    case L'е':
    case L'і':
    case L'и':
    case L'у':
        return 1;
    default:
        return 0;
    }
}

void print_error_and_exit(const char *message)
{
    printf("Termination, reason: %s", message);
    exit(0);
}

int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    return right;
}