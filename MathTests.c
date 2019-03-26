#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

int main(int argc, char **argv) {
    // printf("Init the fork tests\n");
    int x = Fork();

    // if (x == 0) {
    //     int y = 3/0;
    //     if (1) {
    //         TracePrintf(0, "Test 1 failed. y = %u\n", y);
    //     }
    // }

    // x = Fork();
    // if (x == 0) {
    //     float y = 3.0/0;
    //     TracePrintf(0, "The value of y is %u\n", y);
    //     if (1) {
    //         TracePrintf(0, "Test 2 failed.\n");
    //     }
    // }

    x = Fork();
    if (x == 0) {
        int a = 2147483647;
        int b = x * 2;
        TracePrintf(0, "Test 3 Failed. b = %u a = %u\n", b, a);
    }
    return 0;

}
