#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    FILE *fp1;
    FILE *fp2;
	if (argv[1] == NULL){
		printf("Не указано имя копируемого файла\n");
		return 1;
	}
	if (argv[2] == NULL){
		printf("Не указано имя выходного файл\n");
		return 1;
	}
	if ((fp1 = fopen(argv[1], "r")) == NULL) {
        printf("Не удалось открыть файл");
        return 1;
    }
    fp1 = fopen(argv[1], "r");
	struct stat st1;
	stat(argv[1], &st1);

	fp2 = fopen(argv[2], "w");
	char ch;

	while ((ch=getc(fp1))!=EOF){
		putc(ch, fp2);
	}
	chmod(argv[2], st1.st_mode);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
