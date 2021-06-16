#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>
#include "../library/mylib.h"

int main(void)
{
    char *locale = setlocale(LC_ALL, "");

    wprintf(L"Введите предложение:\n");

    wchar_t user_input[255];

    fgetws(user_input, 255, stdin);

    WordsCounter(user_input);

    HowManyKindsOfLetters(user_input);

    HowManyNonLetters(user_input);

    return 0;
}
