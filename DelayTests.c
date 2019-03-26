#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>

/* Created by Patrick Brady and Simran Virk */

int main(int argc, char **argv)
{
    printf("Here. Delay%s\n", argv[0]);
    if (*(argv[0]) == '1') {
        printf("Delay Test 1. Expect a delay of 3.\n");
        // Simple delay Test. Delays the current process for one clock tick.
        if (Delay(3) == ERROR) {
            printf("ERROR!\n");
        }
        printf("Successfully regained control.\n");
    }
    else if (*(argv[0]) == '2') {
        printf("Delay Test 1. Expect instant return.\n");
        // Simple delay Test. Delays the current process for one clock tick.
        if (Delay(0) == ERROR) {
            printf("ERROR!\n");
        }
        printf("This should be instant.\n");
    }
    else if (*(argv[0]) == '3') {
        printf("Delay Test 3. 3 calls to Delay(3). \n");
        // Simple delay Test. Delays the current process for one clock tick.
        if (Delay(3) == ERROR) {
            printf("ERROR!\n");
        }
        printf("1/3\n");
        if (Delay(3) == ERROR) {
            printf("ERROR!\n");
        }
        printf("2/3\n");
        if (Delay(3) == ERROR) {
            printf("ERROR!\n");
        }
        printf("3/3.\n Done.\n");
    }
    else if (*(argv[0]) == '4') {
        printf("Delay Test 4.\n");
        if (Delay(0) == ERROR) {
            printf("ERROR!\n");
        }
        printf("No delay before this should have happeded. Waiting 2 tick\n");
        if (Delay(2) == ERROR) {
            printf("ERROR!\n");
        }
        printf("Wait for 2 tick.\n");
        if (Delay(2) == ERROR) {
            printf("ERROR!\n");
        }
        printf("Wait for 2 tick.\n");
        if (Delay(2) == ERROR) {
            printf("ERROR!\n");
        }
        printf("Done\n");

    }
    return 0;
}
