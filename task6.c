#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


int mygetch(void){
	printf("Нажмите любую клавишу для продолжения...\n");
	int che;
	struct termios oldt, newt;
	tcgetattr((STDIN_FILENO), &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	che = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return che;
}

int main(int argc, char *argv[]) {
    FILE *fp;

	if (argv[1] == NULL){
		printf("Не указано имя файля\n");
		return 1;
	}
	if (argv[2] == NULL){
		printf("Не указано число строк\n");
		return 1;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        return 1;
    }

    fp = fopen(argv[1], "r");
	int count = 0;
	char ch;

	int *lenghts = 0;
	sscanf(argv[2], "%d", &lenghts);

	if (lenghts == 0){
		while ((ch=getc(fp))!=EOF){
			printf("%c", ch);
		}
	}
	else{
		while ((ch=getc(fp))!=EOF){
			printf("%c", ch);
			if (ch == '\n'){
				count++;
			}
			if (count == lenghts){
				mygetch();
				count = 0;
			}
		}
	}
	fclose(fp);
	return 0;
}
