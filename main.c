#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<assert.h>

#define lineLen 50

// Global variables
// minBuffer = int *
// min = int
int numOfPoints;

// Structure for storing points
struct point{
    int x;
    int y;
};

// Structure for args in calcMinDist function
struct args {
    int pidx;           // Index of pointer to calc distance for
    struct point * points;     // Pointer of points array
};

// Create thread function
void *calcMinDist(void *arg) {
    struct args * args = arg;
    int pidx = args->pidx;
    struct point * pointsRef = args->points;
    // printf("(%d, %d)\n", (pointsRef + pidx)->x, (pointsRef + pidx)->y);
    // localMinDist = 0

    // for every point in array
        // if curridx = idx {}
        // else
            // dist = calculate distance
            // if dist < localMinDist
                // localMinDist = dist

    // mindistarray[idx] = localMinDist

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

    printf("Num of points: %d\n", numOfPoints);

    // Allocate memory for minDists []
    int * minDists = malloc(numOfPoints * sizeof(int));

    // Allocate memory for points []
    struct point * points = malloc(numOfPoints * sizeof(struct point));

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

    for(int i = 0; i < numOfPoints; i++) {
        struct args a;
        a.pidx = i;
        a.points = points;
        calcMinDist(&a);
        // printf("(%d, %d)\n", (points + i)->x, (points + i)->y);
    }

    // for every point
        // calculate minimum distance(index, pointer to points array)

    // determine total min distance

    // go through minimum distance array
        // if dist = min dist
            // print out point at that index

    // print min dist

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    fclose(fp);  // Close the file

    return 0;
}