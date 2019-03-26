#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

int main(int argc, char **argv)
{
    printf("Delay Test %s about to run...\n", argv[0]);
    if (*(argv[0]) == '1') {
        printf("Wait Test 1. There are 4 parts...\n");
        int x = Fork();

        if (x == 0) {
            // child 2
            Delay(5);
            return 1;
        }

        // parent
        int y = Fork();
        if (y == 0) {
            // child 3
            Delay(7);
            return 2;
        } 
        // parent
        int z = Fork();
        if (z == 0) {
            // child 4
            Delay(3);
            return 3;
        }
        
        // parent
        int p = Fork();
        if (p == 0) {
            // child 5
            Delay(9);
            return 4;
        }
        int status = 0;
        int pid = Wait(&status);
        if (pid == z && status == 3) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 FAILED. The pid was %u and the status was %u and z is %u\n", pid, status, z);
            return -1;
        }
        pid = Wait(&status);
        if (pid == x && status == 1) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 FAILED.\n");
            return -1;
        }
        pid = Wait(&status);
        if (pid == y && status == 2) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 FAILED.\n");
            return -1;
        }
        pid = Wait(&status);
        if (pid == p && status == 4) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 FAILED.\n");
            return -1;
        }

        // Now do the exact same test again.
        x = Fork();
        if (x == 0) {
            // child 6
            Delay(5);
            // printf("child %u exiting..\n", x);
            return 1;
        }
        // parent
        y = Fork();
        if (y == 0) {
            // child 7
            Delay(7);
            // printf("child %u exiting..\n", y);
            return 2;
        } 
        // parent
        z = Fork();
        if (z == 0) {
            // child 8
            Delay(3);
            // printf("child %u exiting..\n", z);
            return 3;
        }

        // parent
        p = Fork();
        if (p == 0) {
            // child 9
            // printf("child %u exiting..\n", p);
            Delay(9);
            return 4;
        }
        printf("second round of testing...\n");
        status = 0;
        pid = Wait(&status);
        if (pid == z && status == 3) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 FAILED. The pid was %u and the status was %u and z is %u\n", pid, status, z);
            return -1;
        }
        pid = Wait(&status);
        if (pid == x && status == 1) {
            printf("Test 6 passed.\n");
        } else {
            printf("Test 6 FAILED.\n");
            return -1;
        }
        pid = Wait(&status);
        if (pid == y && status == 2) {
            printf("Test 7 passed.\n");
        } else {
            printf("Test 7 FAILED.\n");
            return -1;
        }
        pid = Wait(&status);
        if (pid == p && status == 4) {
            printf("Test 8 passed.\n");
        } else {
            printf("Test 8 FAILED.\n");
            return -1;
        }
        
        
        
    } else if (*(argv[0]) == '2') {
        printf("Wait Test 2. 8 prints.\n");
        int x = Fork();

        if (x == 0) {
            // child 2
            return 1;
        }
        printf(".");
        fflush(stdout);
        Delay(2);
         fflush(stdout);
        // parent
        int y = Fork();
        if (y == 0) {
            // child 3
            return 2;
        } 
        printf(".");
        fflush(stdout);
        Delay(2);
        fflush(stdout);
        // parent
        int z = Fork();
        if (z == 0) {
            // child 4
            return 3;
        }
        printf(".");
        fflush(stdout);
        Delay(2);
        // parent
        int p = Fork();
        if (p == 0) {
            // child 5
            return 4;
        }
        printf(".\n");
        Delay(2);
        int status = 0;
        int pid = Wait(&status);
        if (pid == x && status == 1) {
            printf("Test 1 passed.\n");
        } else {
            printf("Test 1 FAILED.\n");
            return -1;
        }

        
        pid = Wait(&status);
        if (pid == y && status == 2) {
            printf("Test 2 passed.\n");
        } else {
            printf("Test 2 FAILED.\n");
            return -1;
        }

        pid = Wait(&status);
        if (pid == z && status == 3) {
            printf("Test 3 passed.\n");
        } else {
            printf("Test 3 FAILED. The pid was %u and the status was %u and z is %u\n", pid, status, z);
            return -1;
        }
        
        pid = Wait(&status);
        if (pid == p && status == 4) {
            printf("Test 4 passed.\n");
        } else {
            printf("Test 4 FAILED.\n");
            return -1;
        }

        x = Fork();

        if (x == 0) {
            // child 2
            return 1;
        }
        printf(".");
        fflush(stdout);
        Delay(1);

        // parent
        y = Fork();
        if (y == 0) {
            // child 3
            return 2;
        } 
        printf(".");
        fflush(stdout);
        Delay(1);
        // parent
        z = Fork();
        if (z == 0) {
            // child 4
            return 3;
        }
        printf(".");
        fflush(stdout);
        Delay(1);
        // parent
        p = Fork();
        if (p == 0) {
            // child 5
            return 4;
        }
        printf(".\n");
        Delay(1);
        status = 0;
        pid = Wait(&status);
        if (pid == x && status == 1) {
            printf("Test 5 passed.\n");
        } else {
            printf("Test 5 FAILED.\n");
            return -1;
        }

        
        pid = Wait(&status);
        if (pid == y && status == 2) {
            printf("Test 6 passed.\n");
        } else {
            printf("Test 6 FAILED.\n");
            return -1;
        }

        pid = Wait(&status);
        if (pid == z && status == 3) {
            printf("Test 7 passed.\n");
        } else {
            printf("Test 7 FAILED. The pid was %u and the status was %u and z is %u\n", pid, status, z);
            return -1;
        }
        
        pid = Wait(&status);
        if (pid == p && status == 4) {
            printf("Test 8 passed.\n");
        } else {
            printf("Test 8 FAILED.\n");
            return -1;
        }
    } else if (*(argv[0]) == '3') {
        printf("Wait Test 3. \n");
        int x = Fork();
        
        if (x == 0) {
            // Child x
            int y = Fork();
            if (y == 0) {
                Delay(3);
                return 33; // There is no parent to return to. This should still work...
            } else {
                // Parent of y = x
                
                return 11;
            }
        } else {
            // Parent of x = init.
            int status;
            printf("Test 1 about to wait...\n");
            int pid = Wait(&status);
            if (pid != x || status != 11) {
                printf("Test 1 Failed.\n");
            } else {
                printf("Test 1 Success.\n");
            }
            return 22;
        }
    } else if (*(argv[0]) == '4') {
        printf("Tests that processes switch away after 2 clock ticks\n");
        Fork();
        // int pid = GetPid();

        //TODO - possibly a memory leak here. after a while there is a trap memory
        //we dont know why
        
        while (1) {
            // printf("This is process %u\n", pid);
        }
    } else if (*(argv[0]) == '5') {
        printf("This test should print that it is the same process and NEVER switch to idle\n");
        int pid = GetPid();
        
        while (1) {
            printf("This is process %u\n", pid);
        }
        
    }
    return 0;
}