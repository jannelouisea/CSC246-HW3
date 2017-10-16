#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

#define lineLen 50

// Global variables
// minBuffer = int *
// min = int

// Structure for storing points
struct point{
    int x;
    int y;
};

// Structure for args in calcMinDist function
struct args {
    int numOfPoints;
    int idx;
    // pointer to points array
};

// Create thread function
void * calcMinDist(void * args) {
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
    char * fname;

    if(argv[1] != NULL) {
        fname = argv[1];
    } else {
        printf("Pass a file with the co-ordinates\n");
    }

    fp = fopen(fname, "r");  // Open file

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    int numOfPoints = 0;
    char * line[lineLen];

    // Get the number of points in the file
    if (fgets(line, sizeof(line), fp) != NULL) {
        numOfPoints = (int) strtol(line, NULL, 10);
    } else {
        printf("Could not properly read file\n");
    }

    printf("Num of points: %d\n", numOfPoints);

    // Allocate memory for minDists []

    // Allocate memory for points []

    // Read file until null and store points in points structure

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