#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_MAX 100000

char polje[N_MAX];

int main(int argc, char** argv) {
	srand(time(NULL));

	if (argc < 2) {
		puts("Not enough arguments");
		exit(1);
	}

	char* end = NULL;
	long i, n = strtol(argv[1], &end, 10);

	if (end - argv[1] != strlen(argv[1])) {
		puts("Given argument is not a valid number");
		exit(2);
	}

	if (n < 1 || n > N_MAX) {
		printf("Argument outside of allowed range: 1 - %d\n", N_MAX);
	}

	for (i = 0; i < n; i++) {
		int r = (rand() & 1) ? 1 : -1;
		polje[i] = r;
	}

	for (i = 0; i < n; i++) {
		puts(polje[i] == 1 ? "1" : "-1");
	}

	getchar();

	return 0;
}
