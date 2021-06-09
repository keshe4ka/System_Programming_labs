#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>

void HowManyKindsOfLetters(wchar_t user_input[255])
{
    //перевод строки в нижний регистр
    wchar_t c;
    int i = 0;
    while (user_input[i])
    {
        c = user_input[i];
        user_input[i] = towlower(c);
        i++;
    }

    //заполняем алфавит (русские и английские строчные)
    wchar_t alphabet[118];
    int k = 0;
    for (wchar_t i = L'а'; i <= L'я'; i++)
    {
        alphabet[k] = i;
        k++;
    }
    for (wchar_t i = L'a'; i <= L'z'; i++)
    {
        alphabet[k] = i;
        k++;
    }
    alphabet[58] = L'ё';

    //счетчик уникальных букв
    int uniq_letters = 0;

    for (int i = 0; i < wcslen(alphabet); i++)
    {
        for (int j = 0; j < wcslen(user_input); j++)
        {
            if (alphabet[i] == user_input[j])
            {
                uniq_letters++;
                break;
            }
        }
    }
    wprintf(L"Количество различных используемых букв: %d\n", uniq_letters);
}