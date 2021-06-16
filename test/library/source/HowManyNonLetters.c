#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>



void HowManyNonLetters(wchar_t user_input[255])
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

    //счетчик небукв
    bool letter = true;
    int nonletters = -1;
    for (int i = 0; i < wcslen(user_input); i++)
    {
        for (int j = 0; j < wcslen(alphabet); j++)
        {
            if (user_input[i] == alphabet[j])
            {
                letter = true;
                break;
            }
            else
            {
                letter = false;
            }
        }
        if (letter == false)
        {
            nonletters++;
        }
    }
    wprintf(L"Количество небукв: %d\n", nonletters);
}
