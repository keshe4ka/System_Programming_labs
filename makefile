task1: task1.c
	gcc -o task1 task1.c 
task2: task2.c WordsCounter.c HowManyKindsOfLetters.c HowManyNonLetters.c
	gcc -o task2 task2.c WordsCounter.c HowManyKindsOfLetters.c HowManyNonLetters.c
task5: task5.c
	gcc -o task5 task5.c
task8: task8.c 
	gcc -o task8 task8.c