#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define STR_ARR_LEN 3

//////// add initialization code for condition variable here ////////

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

        //////// add condition variable synchronization here ////////


        // print string in sequence.
        printf("%s\n", str_pt[i%STR_ARR_LEN]);

        //////// add condition variable synchronization here ////////


        i++;
    }
    printf("Thread 0 total count %u\n",i);
    return NULL;
}

// Start routine for thread1
void *thread1(void *arg) {
    char ** str_pt = (char **)arg;
    unsigned i=0;
    while (running) {

        //////// add condition variable synchronization here ////////

        // print string in sequence.
        printf("%s\n", str_pt[i%STR_ARR_LEN]);

        //////// add condition variable synchronization here ////////

        i++;
    }
    printf("Thread 1 total count %u\n",i);

    return NULL;
}

// Start routine for thread2
void *thread2(void *arg) {
    char ** str_pt = (char **)arg;
    unsigned i=0;
    while (running) {

        //////// add condition variable synchronization here ////////

        // print string in sequence.
        printf("%s\n", str_pt[i%STR_ARR_LEN]);

        //////// add condition variable synchronization here ////////

        i++;
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