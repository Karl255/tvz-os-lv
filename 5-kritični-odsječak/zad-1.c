#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define N 100
int mjesta[N];
pthread_mutex_t mutexes[N];

void mutexes_init();
void mutexes_destroy();

void* korisnik(void* _) {
	sleep((rand() % 5) + 1); // 1-5 s
	
	while (1) {
		int mjesto_i = rand() % N;
		
		pthread_mutex_lock(&mutexes[mjesto_i]);
		
		if (mjesta[mjesto_i] == 0) {
			if (rand() & 1) { // 50%
				sleep((rand() % 2) + 1); // 1-2 s
				mjesta[mjesto_i]++;
				
				pthread_mutex_unlock(&mutexes[mjesto_i]);
				break;
			}
		}
		
		pthread_mutex_unlock(&mutexes[mjesto_i]);
	}
	
	return 0;
}

int main(int argc, char** argv) {
	int i, odmah;
	pthread_t korisnici[N];
	
	mutexes_init();
	srand(time(NULL));
	
	odmah = rand() % N;
	printf("%d putnika nije bilo spojeno na mobilnu mrežu!\n", N - odmah);
	
	for (i = 0; i < odmah; i++) {
		int status = pthread_create(&korisnici[i], NULL, korisnik, NULL);
		
		if (status != 0) {
			fprintf(stderr, "Couldn't create new thread (%d). Exiting.\n", i);
			exit(1);
		}
	}
	
	for (i = odmah; i < N; i++) {
		int status = pthread_create(&korisnici[i], NULL, korisnik, NULL);
		
		if (status != 0) {
			fprintf(stderr, "Couldn't create new thread (%d). Exiting.\n", i);
			exit(1);
		}
	}
	
	for (i = 0; i < N; i++) {
		pthread_join(korisnici[i], NULL);
	}
	
	int praznih = 0;
	
	for (i = 0; i < N; i++) {
		printf("%d ", mjesta[i]);
		
		if (i % 10 == 9) {
			puts("");
		}
		
		if (mjesta[i] == 0) {
			praznih++;
		}
	}
	
	printf("praznih = %d\n", praznih);
	mutexes_destroy();
	
	return 0;
}

void mutexes_init() {
	int i = 0;
	
	for (i = 0; i < N; i++) {
		pthread_mutex_init(&mutexes[i], NULL);
	}
}

void mutexes_destroy() {
	int i = 0;
	
	for (i = 0; i < N; i++) {
		pthread_mutex_destroy(&mutexes[i]);
	}
}
