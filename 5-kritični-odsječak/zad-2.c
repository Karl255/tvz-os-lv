#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define N 100
int mjesta[N];

typedef enum {
	EMPTY,
	COKOLADA,
	CEVAPI,
	JANJETINA,
	STRUKLE,
	GRAH,
	KEKSI,
	KELJ,
	JABUKA,
	FOOD_COUNT
} Food;

typedef struct {
	int times_eaten;
	int times_rejected;
	int times_empty;
} Counters;

void Counters_init(Counters*);
void Counters_print(const char*, Counters*);

Food table = EMPTY;
pthread_mutex_t table_mutex;

void* tin_sim(void*);
void* davor_sim(void*);
void* ivica_sim(void*);
void* ivan_sim(void*);
void* kuharica_sim(void*);

void sim_sleeping(const char*);
void sim_programming(const char*);
void sim_eating(const char*);
void sim_car_servicing(const char*);
void sim_watching_tv(const char*);
void sim_playing_tennis(const char*);
void sim_listening_to_piano_music(const char*);

void sim_cooking();
int sim_serving_food();
void sim_resting();

int rand_in_range(int, int);

int main(int argc, char** argv) {
	srand(time(NULL));
	
	if (argc < 2) {
		puts("Not enough arguments");
		exit(1);
	}
	
	char* end = NULL;
	int foods = strtol(argv[1], &end, 10);
	
	if (*end != '\0' || foods < 1) {
		puts("Given argument invalid");
		exit(1);
	}
	
	pthread_mutex_init(&table_mutex, NULL);
	
	pthread_t tin, davor, ivica, ivan, kuharica;
	Counters tins_counter, davors_counter, ivicas_counter, ivans_counter;
	
	Counters_init(&tins_counter);
	Counters_init(&davors_counter);
	Counters_init(&ivicas_counter);
	Counters_init(&ivans_counter);
	
	pthread_create(&tin, NULL, tin_sim, &tins_counter);
	pthread_create(&davor, NULL, davor_sim, &davors_counter);
	pthread_create(&ivica, NULL, ivica_sim, &ivicas_counter);
	pthread_create(&ivan, NULL, ivan_sim, &ivans_counter);
	
	pthread_create(&kuharica, NULL, kuharica_sim, &foods);
	pthread_join(kuharica, NULL);
	
	sleep(10); // let everything play out
	
	pthread_cancel(tin);
	pthread_cancel(davor);
	pthread_cancel(ivica);
	pthread_cancel(ivan);
	
	puts("");
	Counters_print("Tin", &tins_counter);
	Counters_print("Davor", &davors_counter);
	Counters_print("Ivica", &ivicas_counter);
	Counters_print("Ivan", &ivans_counter);
	
	return 0;
}

// util

int rand_in_range(int start, int end) {
	return (rand() % (end - start + 1)) + start;
}

void Counters_init(Counters* counters) {
	counters->times_eaten = 0;
	counters->times_rejected = 0;
	counters->times_empty = 0;
}

void Counters_print(const char* name, Counters* counters) {
	printf("%s\neaten: %d\nrejected: %d\nempty: %d\n", name, counters->times_eaten, counters->times_rejected, counters->times_empty);
}

// threads

void* tin_sim(void* arg) {
	Counters* counters = arg;
	char* name = "Tin";
	int took_food = 0;
	
	while (1) {
		sim_sleeping(name);
		sim_sleeping(name);
		sim_programming(name);
		
		pthread_mutex_lock(&table_mutex);
		
		switch (table) {
			case EMPTY:
				counters->times_empty++;
				took_food = 0;
				break;
			
			case CEVAPI:
			case JANJETINA:
				counters->times_rejected++;
				took_food = 0;
				break;
			
			default:
				counters->times_eaten++;
				took_food = 1;
				table = EMPTY;
				break;
		}
		
		pthread_mutex_unlock(&table_mutex);
		
		if (took_food) {
			sim_eating(name);
		}
		
		sim_car_servicing(name);
	}
	
	return NULL;
}

void* davor_sim(void* arg) {
	Counters* counters = arg;
	char* name = "Davor";
	int took_food = 0;
	
	while (1) {
		sim_sleeping(name);
		sim_programming(name);
		
		pthread_mutex_lock(&table_mutex);
		
		switch (table) {
			case EMPTY:
				counters->times_empty++;
				took_food = 0;
				break;
			
			case COKOLADA:
			case KEKSI:
				counters->times_rejected++;
				took_food = 0;
				break;
			
			default:
				counters->times_eaten++;
				took_food = 1;
				table = EMPTY;
				break;
		}
		
		pthread_mutex_unlock(&table_mutex);
		
		if (took_food) {
			sim_eating(name);
		}
		
		sim_watching_tv(name);
	}
	
	return NULL;
}

void* ivica_sim(void* arg) {
	Counters* counters = arg;
	char* name = "Ivica";
	int took_food = 0;
	
	while (1) {
		sim_sleeping(name);
		sim_playing_tennis(name);
		
		pthread_mutex_lock(&table_mutex);
		
		switch (table) {
			case EMPTY:
				counters->times_empty++;
				took_food = 0;
				break;
			
			case GRAH:
			case KELJ:
				counters->times_rejected++;
				took_food = 0;
				break;
			
			default:
				counters->times_eaten++;
				took_food = 1;
				table = EMPTY;
				break;
		}
		
		pthread_mutex_unlock(&table_mutex);
		
		if (took_food) {
			sim_eating(name);
		}
		
		sim_programming(name);
	}
	
	return NULL;
}

void* ivan_sim(void* arg) {
	Counters* counters = arg;
	char* name = "Ivan";
	int took_food = 0;
	
	while (1) {
		sim_sleeping(name);
		sim_listening_to_piano_music(name);
		
		pthread_mutex_lock(&table_mutex);
		
		switch (table) {
			case EMPTY:
				counters->times_empty++;
				took_food = 0;
				break;
			
			case STRUKLE:
				counters->times_rejected++;
				took_food = 0;
				break;
			
			default:
				counters->times_eaten++;
				took_food = 1;
				table = EMPTY;
				break;
		}
		
		pthread_mutex_unlock(&table_mutex);
		
		if (took_food) {
			sim_eating(name);
		}
		
		sim_programming(name);
	}
	
	return NULL;
}

void* kuharica_sim(void* n) {
	int ingredients = *(int*)n;
	
	while (ingredients > 0) {
		sim_cooking();
		
		if (sim_serving_food()) {
			ingredients--;
		}
		
		sim_resting();
	}
	
	return NULL;
}

// simulations

void sim_sleeping(const char* name) {
	printf("%s is sleeping\n", name);
	sleep(rand_in_range(5, 10));
}

void sim_programming(const char* name) {
	printf("%s is programming\n", name);
	int i, factorial = 1, n = (rand() % 10) + 1;
	
	for (i = n; i >= 2; i--) {
		factorial *= i;
	}
}

void sim_eating(const char* name) {
	printf("%s is eating\n", name);
	sleep(rand_in_range(2, 4));
}

void sim_car_servicing(const char* name) {
	printf("%s is getting his car serviced\n", name);
	int chance = rand_in_range(0, 100);
	
	if (chance < 25) {
		sleep(4);
	} else if (chance < 25 + 20) {
		sleep(2);
	} else {
		sleep(rand_in_range(2, 4));
	}
}

void sim_watching_tv(const char* name) {
	printf("%s is watching TV\n", name);
	sleep(rand_in_range(2, 4));
}

void sim_playing_tennis(const char* name) {
	printf("%s is playing tennis\n", name);
	sleep(rand_in_range(2, 4));
}

void sim_listening_to_piano_music(const char* name) {
	printf("%s is listening to piano music\n", name);
	sleep(rand_in_range(2, 4));
}

void sim_cooking() {
	puts("Kuharica is cooking");
	sleep(rand_in_range(1, 2));
}

int sim_serving_food() {
	puts("Kuharica is serving food");
	int consumed_ingredient = 0;
	
	pthread_mutex_lock(&table_mutex);
	
	if (table == EMPTY) {
		table = (rand() % (FOOD_COUNT - 1)) + 1;
		consumed_ingredient = 1;
	}

	pthread_mutex_unlock(&table_mutex);
	
	return consumed_ingredient;
}

void sim_resting() {
	puts("Kuharica is resting");
	sleep(rand_in_range(1, 2));
}
