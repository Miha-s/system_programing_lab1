#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include <locale.h>
#include "vector.h"
#include "helpers.h"

int run(int argc, char **argv);

FILE *open_document(int argc, char **argv);

// NULL if unsuccess
wchar_t *get_next_word(FILE *document);

void parse_word(StringsVector_t *highest_words, wchar_t *word);

void print_result(StringsVector_t *vector);


int main(int argc, char **argv)
{
    return run(argc, argv);
}

int run(int argc, char **argv)
{

    FILE *document = open_document(argc, argv);
    if (document == NULL)
    {
        print_error_and_exit("failed to open file");
    }
    
    StringsVector_t *highest_words = create_vector();

    wchar_t *new_word = get_next_word(document);

    while (new_word != NULL)
    {
        parse_word(highest_words, new_word);

        new_word = get_next_word(document);
    }

    print_result(highest_words);
    free_vector(highest_words);
}


FILE *open_document(int argc, char **argv)
{
    if (argc < 2)
        return NULL;

    setlocale(LC_ALL, "uk_UA.UTF-8");

    const char only_read_mode[] = "r";
    FILE *new_document = fopen(argv[1], only_read_mode);

    return new_document;
}

wchar_t *get_next_word(FILE *document)
{
    wchar_t *new_word_placeholder = malloc(sizeof(wchar_t *) * max_word_length);
    int pointer = 0;
    wchar_t character = fgetwc(document);

    while (character != WEOF && !is_character(character))
    {
        // skipping all delimiters
        character = fgetwc(document);
    }

    while (character != WEOF && is_character(character))
    {
        new_word_placeholder[pointer] = character;
        pointer++;
        character = fgetwc(document);
    }


    if (pointer == 0)
    {
        free(new_word_placeholder);
        return NULL;
    }
    else
    {
        new_word_placeholder[pointer] = '\0';
        return new_word_placeholder;
    }
}

int compare_highest_and_current_word(StringsVector_t *highest_words, const wchar_t *word);

void parse_word(StringsVector_t *highest_words, wchar_t *word)
{
    int comparison_result = compare_highest_and_current_word(highest_words, word);
    if (comparison_result < 0)
    {
        free(word);
        return;
    }
    if (comparison_result == 0)
    {
        add_unique_to_vector(highest_words, word);
        return;
    }
    // comparison_result > 0
    clear_vector(highest_words);
    add_unique_to_vector(highest_words, word);
}

void print_result(StringsVector_t *vector)
{
    for (int i = 0; i < vector->size; i++)
    {
        printf("%S\n", vector->strings[i]);
    }
}


int evaluate_word(const wchar_t *word);

// 1 - word > highest; 0 - word = highest; -1 word < highest
int compare_highest_and_current_word(StringsVector_t *highest_words, const wchar_t *word)
{
    static const int word_bigger = 1;
    static const int word_equal = 0;
    static const int word_lesser = -1;

    if (highest_words->size == 0)
    {
        return word_bigger;
    }
    const int word_score = evaluate_word(word);
    const int current_highest_score = evaluate_word(highest_words->strings[0]);

    if (word_score > current_highest_score)
    {
        return word_bigger;
    }
    else if (word_score < current_highest_score)
    {
        return word_lesser;
    }
    else
    {
        return word_equal;
    }
}

int evaluate_word(const wchar_t *word)
{
    int max_vowels = 0;
    int current_vowels = 0;
    int pointer = 0;
    while (word[pointer])
    {
        if (is_vowel(word[pointer]))
        {
            current_vowels++;
        }
        else
        {
            max_vowels = max(max_vowels, current_vowels);
            current_vowels = 0;
        }
        pointer++;
    }
    return max(max_vowels, current_vowels);
}

