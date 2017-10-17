#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<assert.h>

#define lineLen 50

// Structure for storing points
struct point {
    int x;
    int y;
    double mindist;
};

// Structure for args in calcMinDist function
struct args {
    int pidx;                   // Index of point in points[] to calc distance for
};

// Global variables
int numOfPoints;
double * minDists;
struct point * points;
double globalMinDist = -1;

pthread_mutex_t lock    = PTHREAD_MUTEX_INITIALIZER;

// Create thread function
void *calcMinDist(void *arg) {
    const int *pidx = arg;

    double localMinDist = -1.0;
    double x1, y1, x2, y2, dist2, dist;
    x1 = (double) (points + *pidx)->x;
    y1 = (double) (points + *pidx)->y;

    for (int i = 0; i < numOfPoints; i++) {
        if (*pidx == i) {
        }
        else {
            // Distance formula d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
            x2 = (double) (points + i)->x;
            y2 = (double) (points + i)->y;
            dist2 = fabs(pow((x2 - x1), 2) + pow((y2 - y1), 2));
            dist = sqrt(dist2);

            if (localMinDist == -1.0) {
                localMinDist = dist;
            } else {
                if (dist < localMinDist)
                    localMinDist = dist;
            }
        }
    }

    pthread_mutex_lock(&lock);
    (points + *pidx)->mindist = localMinDist;
    pthread_mutex_unlock(&lock);
}


int main(int argc, char *argv[])
{
    FILE * fp;
    char * fname = NULL;

    if(argv[1] != NULL) {
        fname = argv[1];
    } else {
        printf("Pass a file with the co-ordinates\n");
    }

    fp = fopen(fname, "r");  // Open file

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    numOfPoints = 0;
    char line[lineLen];

    // Get the number of points in the file
    if (fgets(line, sizeof(line), fp) != NULL) {
        numOfPoints = (int) strtol(line, NULL, 10);
    } else {
        printf("Could not properly read file\n");
    }

    // Allocate memory for minDists []
    minDists = malloc(numOfPoints * sizeof(double));

    // Allocate memory for points []
    points = malloc(numOfPoints * sizeof(struct point));

    int idx = 0;

    // Read file until null and store points in points structure
    while (fgets(line, sizeof(line), fp) != NULL) {
        char * x = strtok(line, " ");
        char * y = strtok(0, " ");

        (points + idx)->x = (int) strtol(x, NULL, 10);
        (points + idx)->y = (int) strtol(y, NULL, 10);

        idx++;
    }
    assert(numOfPoints == idx);

    // Handle for each thread
    pthread_t thread[numOfPoints];

    int args[numOfPoints];

    for(int i = 0; i < numOfPoints; i++) {
        args[i] = i;

        if (pthread_create(thread + i, NULL, calcMinDist, &args[i]) != 0) {
            fprintf(stderr, "Error: Cannot create thread %d\n", i);
            exit(1);
        }
    }

    // Let threads run for a few seconds
    sleep(1);
    for(int i = 0; i < numOfPoints; i++) {
        pthread_join(thread[i], NULL);
    }

    // Finding global min distance not in threads
    for(int i = 0; i < numOfPoints; i++) {
        // printf("%d (%d, %d) %f \n", i, (points + i)->x, (points + i)->y, (points+i)->mindist);
        if (globalMinDist == -1.0) {
            globalMinDist = (points + i)->mindist;
        } else {
            if ((points + i)->mindist < globalMinDist)
                globalMinDist = (points + i)->mindist;
        }
    }

    for(int i = 0; i < numOfPoints; i++) {
        if ((points + i)->mindist == globalMinDist) {
            printf("(%d, %d) ", (points + i)->x, (points + i)->y);
        }
    }
    printf("%.4f\n", globalMinDist);

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    fclose(fp);  // Close the file

    return 0;
}