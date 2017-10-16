#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

// Global variables
// minBuffer = int *
// min = int

//Structure for storing points
struct point{
    int x;
    int y;
};

// Structure of args for each thread

// Find the distance between two points
// d = sqrt((x2-x1)^2 - (y2-y1)^2);

// Create thread function


int main(int argc, char *argv[])
{
    FILE * fp;
    char * fname;

    if(argv[1] != NULL) {
        fname = argv[1];
    } else {
        printf("Pass a file with the co-ordinates\n");
        return 0;
    }

    fp = fopen(fname, "r");  //Open file
    // Check if the file pointer is null.

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Get the number of points in the file
    int numOfPoints = (int) strol();

    // Store each points in a points array

    // Create a thread to calculate the minimum distance for each point

    // Read the minBuffer to
    // If the value in the minBuffer equals the min
    // Print out the point with that index

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    fclose(fp);  //Close the file

    return 0;
}