#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

/*
//потоковая функция
//для выхода при помощи Ctrl+Q
void *threadFunc(void *thread_data) {
    if (GetAsyncKeyState(81) == -32767) {
        if (GetAsyncKeyState(17) == -32767) {
            exit(0);
        }
    }
}
 */

int main(int argc, char *argv[]) {

    /*
    void* thread_data = NULL;
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunc, thread_data);
     */
    FILE *fp;

    if ((fp = fopen(argv[1], "w")) == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        return 1;
    }

    char *locale = setlocale(LC_ALL, "");
    printf("Введите текст для записи:\n");

    char user_input[255];

    fp = fopen(argv[1], "w");

    fgets(user_input, 255, stdin);

    for (int i = 0; i < strlen(user_input); i++) {
        putc(user_input[i], fp);
    }
    fclose(fp);
    //pthread_join(thread, NULL);
    return 0;
}
