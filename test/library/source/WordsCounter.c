#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <locale.h>



void WordsCounter(wchar_t user_input[255])
{
    int words = 0;
    for (int i = 0; i < wcslen(user_input); i++)
    {
        if (user_input[i] == ' ' && user_input[i + 1] != ' ')
        {
            words++;
        }
    }
    if (user_input[0] != ' ')
        words++;
    wprintf(L"Количество слов в строке: %d\n", words);
}
