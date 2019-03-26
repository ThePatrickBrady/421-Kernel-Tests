#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

/* Created by Patrick Brady and Simran Virk */

int recFact(int n);

int main(int argc, char **argv) {
    if (*(argv[0]) == '1') {
        printf("Starting memory test\n");
        
        int x = recFact(500);
        printf("Test 4 passed");

        int y = Fork();
        int s = recFact(1000);
        if (y == 0) {
            printf("Test 2 passed");
        } else {
            printf("Test 3 passed");
        }

    }
    return 0;

}


int recFact(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * recFact(n - 1);
    }
}
