#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define STR_ARR_LEN 3
#define NUM_OF_THREADS 3
#define THREAD0 0
#define THREAD1 1
#define THREAD2 2

//////// add initialization code for condition variable here ////////
pthread_mutex_t lock    = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond0     = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond1     = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2     = PTHREAD_COND_INITIALIZER;
unsigned thread          = 0;


// Print an error message and exit on an error
void fail(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

// Global variable, to tell all the threads when it's time to stop.
volatile int running = 1;

// Start routine for thread0
void *thread0(void *arg) {
    char ** str_pt = (char **)arg;
    unsigned i=0;
    while (running) {

        // add code to wait
        pthread_mutex_lock(&lock);
        while (thread != THREAD0) {
            pthread_cond_wait(&cond0, &lock);
        }
        pthread_mutex_unlock(&lock);

        //////// add condition variable synchronization here ////////
        pthread_mutex_lock(&lock);
        // print string in sequence.
        if (running) {
            printf("%s\n", str_pt[i%STR_ARR_LEN]);
            i++;
        }
        thread = 2;
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&lock);
        //////// add condition variable synchronization here ////////
    }
    printf("Thread 0 total count %u\n",i);
    return NULL;
}

// Start routine for thread1
void *thread1(void *arg) {
    char ** str_pt = (char **)arg;
    unsigned i=0;
    while (running) {

        // add code to wait
        pthread_mutex_lock(&lock);
        while (thread != THREAD1) {
            pthread_cond_wait(&cond1, &lock);
        }
        pthread_mutex_unlock(&lock);

        //////// add condition variable synchronization here ////////
        pthread_mutex_lock(&lock);
        // print string in sequence.
        if (running) {
            printf("%s\n", str_pt[i%STR_ARR_LEN]);
            i++;
        }
        thread = 0;
        pthread_cond_signal(&cond0);
        pthread_mutex_unlock(&lock);
        //////// add condition variable synchronization here ////////
    }
    printf("Thread 1 total count %u\n",i);

    return NULL;
}

// Start routine for thread2
void *thread2(void *arg) {
    char ** str_pt = (char **)arg;
    unsigned i=0;
    while (running) {

        // add code to wait
        pthread_mutex_lock(&lock);
        while (thread != THREAD2) {
            pthread_cond_wait(&cond2, &lock);
        }
        pthread_mutex_unlock(&lock);

        //////// add condition variable synchronization here ////////
        pthread_mutex_lock(&lock);
        // print string in sequence.
        if (running) {
            printf("%s\n", str_pt[i%STR_ARR_LEN]);
            i++;
        }
        thread = 1;
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
        //////// add condition variable synchronization here ////////
    }
    printf("Thread 2 total count %u\n",i);

    return NULL;
}


// Main program, make all the threads, let them run for a while,
// then tell them to stop.
int main(int argc, char *argv[]) {

    // prepare string for each thread
    char * str_array0[STR_ARR_LEN] = {"alpha", "delta", "eta"};
    char * str_array1[STR_ARR_LEN] = {"gamma", "zeta", "iota"};
    char * str_array2[STR_ARR_LEN] = {"beta", "epsilon", "theta"};

    // Handle for each thread.
    pthread_t thread[3];

    if (pthread_create(thread + 0, NULL, thread0, str_array0) != 0)
        fail("Can't create thread0.\n");
    if (pthread_create(thread + 1, NULL, thread1, str_array1) != 0)
        fail("Can't create thread1.\n");
    if (pthread_create(thread + 2, NULL, thread2, str_array2) != 0)
        fail("Can't create thread2.\n");

    // Let the threads run for a few seconds.
    sleep(1);
    running = 0;
    int i;
    for (i = 0; i < 3; i++)
        pthread_join(thread[i], NULL);

    return EXIT_SUCCESS;
}