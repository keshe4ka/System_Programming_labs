#include <stdio.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char filename[] = argv[1];
    FILE *fp;

    char *locale = setlocale(LC_ALL, "");
    printf("Для выхода из программы нажмите Ctrl + Q\nВведите текст для записи:\n");

    wchar_t user_input[255];


    fgetws(user_input, 255, stdin);

    /*
    if (GetAsyncKeyState(81) == -32767) {
        if (GetAsyncKeyState(17) == -32767) {
            exit(0);
        }
    }
     */


    if ((fp = fopen(argv[1], "w")) == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        return 1;
    }
}