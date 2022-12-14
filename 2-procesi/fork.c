#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// https://www.gnu.org/software/libc/manual/html_node/Creating-a-Process.html

int main(int argc, char** argv) {
	setbuf(stdout, NULL);
	
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

	if (n < 1) {
		printf("Argument can't be less than 1\n");
		exit(3);
	}
	
	int errors = 0;
	
	for (i = 1; i <= n; i++) {
		switch (fork()) {
			case -1:
				errors++;
				break;
			
			case 0:
				printf("Dijete #%ld\n", i);
				exit(0);
			
			default:
				printf("Roditelj #%ld\n", i);
				break;
		}
	}
	
	fprintf(stderr, "Errors: %d\n", errors);
	
	return 0;
}
