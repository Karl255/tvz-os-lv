#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

long sum = 0;

void* korisnik(void* wait_time) {
	sum++;
	return 0;
}

int main(int argc, char** argv) {
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
	
	long created = 0;
	
	for (i = 1; i <= n; i++) {
		pthread_t thread;
		int status = pthread_create(&thread, NULL, korisnik, NULL);
		
		if (status != 0) {
			fprintf(stderr, "Couldn't create new thread (%ld). Exiting.\n", i);
			break;
		}
		
		created++;
	}
	
	printf("%ld %ld\n", created, sum);
	
	return 0;
}
