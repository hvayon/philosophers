#define _CRT_SECURE_NO_WARNINGS
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
//------
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

sem_t *semaphore;
 
static int counter = 0;
 
void	* worker1(void* args) {
    int i;
    int local;
    for (i = 0; i < 100; i++) {
        local = counter;
        printf("worker1 - %d\n", local);
        local++;
        counter = local;
        sleep(1);
		sem_post(semaphore);
    }
	return(NULL);
}
 
void* worker2(void* args) {
    int i;
    int local;
    for (i = 0; i < 100; i++) {
        local = counter;
        printf("worker 2 - %d\n", local);
        local--;
        counter = local;
        sleep(1);
		sem_post(semaphore);
    }
	return(NULL);
}
 
int main(void) {
    pthread_t thread1;
    pthread_t thread2;
	const char *start;
 
	semaphore = sem_open(start, 0);
    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
 
    printf("== %d", counter);
	return(0);
}