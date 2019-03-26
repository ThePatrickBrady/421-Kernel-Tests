#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>

/* Created by Patrick Brady and Simran Virk */

int main(int argc, char **argv)
{
    printf("Running Exec Test number %s.\n", argv[0]);
    if (*(argv[0]) == '1') {
        printf("Exec Test 1...\n");
    }
    else if (*(argv[0]) == '2') {
        printf("Exec Test 2...\n");
    }
    else if (*(argv[0]) == '3') {
        printf("Exec Test 3...\n");
    }
    else if (*(argv[0]) == '4') {
        printf("Exec Test 4...\n");

    }
    return 0;
}
