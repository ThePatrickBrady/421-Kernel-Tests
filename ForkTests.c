#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>

/* Created by Patrick Brady and Simran Virk */

int main(int argc, char **argv) {
    printf("Init the fork tests\n");
    if (*argv[1] == '1') {
        //Test one fork
        int x;
        x = Fork();
        if (x == 0) {
            printf("\nHello from child\n");
        } else {
            printf("\nHello from parent\n");
        }

        return 0;
    }

    if (*argv[1] == '2') {
        //Test multiple forks
        int x = Fork();
        int y = Fork();
        int z = Fork();
        int s;

        //TODO - May want to test that region 0 page tables are freed here.
        int pid = GetPid();
        printf("\n Hello from process %u\n", pid);
        Delay(3);
        printf("\n Goodbye from process %u\n", pid);

        if (x != 0 && y != 0 && z != 0) {
            Wait(&s);
            Wait(&s);
            Wait(&s);

            Delay(10);
            Fork();
        }

        return 0;
    }

    if (*argv[1] == '3') {
        int x = Fork();
        int y = Fork();
        int s1,s2,s3,s4,s5,s6;

        if (x != 0 && y != 0) {
            // The OG parent
            int w1 = Wait(&s1);
            if (s1 != ERROR) {
                printf("\nPASSED TEST: Process %u exited with status %u.\n", w1, s1);
            } else {
                printf("\nFAILED TEST: Expected status 0 from child but got %u\n", s1);
                return -1;
            }

            int w2 = Wait(&s2);
            if (s2 != ERROR) {
                printf("\nPASSED TEST: Process %u exited with status %u.\n", w2, s2);
            } else {
                printf("\nFAILED TEST: Expected status 0 from child but got %u\n", s2);
                return -1;
            }

            if (!((s1 == 10 && s2 == 20) || (s1 == 20 && s2 == 10))) {
                printf("\nFAILED TEST: Status is incorrect for the children. s1 = %u and s2 = %u", s1, s2);
                return -1;
            }

            int w3 = Wait(&s3);
            if (w3 == ERROR) {
                printf("\nPASSED TEST: No more children for proc %u left to wait for.\n", GetPid());
            } else {
                printf("\nFAILED TEST: Expected ERROR but got %u as exiting child\n", w3);
                return -1;
            }
            
        } else if (y != 0) {
            // Has one child
            int w4 = Wait(&s4);

            if (s4 != 10) {
                printf("\nPASSED TEST: Process %u exited with status %u.\n", w4, s4);
            } else {
                printf("\nFAILED TEST: Expected status 0 from child but got %u\n", s4);
                return -1;
            }

            int w5 = Wait(&s5);
            if (w5 == ERROR) {
                printf("\nPASSED TEST: No more children left for proc %u to wait for.\n", GetPid());
            } else {
                printf("\nFAILED TEST: Expected ERROR but got %u as exiting child\n", w5);
                return -1;
            }
            return 10;
        }  else {
            // No children >:) anymore
            int w6 = Wait(&s6);
            if (w6 == ERROR) {
                printf("\nPASSED TEST: No more children left for proc %u to wait for.\n", GetPid());
            } else {
                printf("\nFAILED TEST: Expected ERROR but got %u as exiting child\n", w6);
                return -1;
            }
            return 20;
        }
    }


    
    return 0;
}
