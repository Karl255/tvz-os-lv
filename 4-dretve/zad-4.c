#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <time.h>
#include <unistd.h>

int mjesta[10][10];

void* korisnik(void* wait_time) {
	sleep((rand() % 5) + 1); // 1-5 s
	
	while (1) {
		int mjesto_x = rand() % 10;
		int mjesto_y = rand() % 10;
		
		if (mjesta[mjesto_y][mjesto_x] == 0) {
			if (rand() & 1) { // 50%
				sleep((rand() % 2) + 1); // 1-2 s
				mjesta[mjesto_y][mjesto_x]++;
				break;
			}
		}
	}
	
	return 0;
}

int main(int argc, char** argv) {
	long i, j;
	pthread_t korisnici[100];
	
	srand(time(NULL));
	
	for (i = 0; i < 100; i++) {
		int status = pthread_create(&korisnici[i], NULL, korisnik, NULL);
		
		if (status != 0) {
			fprintf(stderr, "Couldn't create new thread (%ld). Exiting.\n", i);
			exit(1);
		}
	}
	
	for (i = 0; i < 100; i++) {
		pthread_join(korisnici[i], NULL);
	}
	
	int sum = 0;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d ", mjesta[i][j]);
			sum += mjesta[i][j];
		}
		
		puts("");
	}
	
	printf("sum = %d\n", sum);
	
	return 0;
}
