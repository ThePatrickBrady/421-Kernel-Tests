#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>
#include <comp421/hardware.h>

/* Created by Patrick Brady and Simran Virk */

int main(int argc, char **argv) {
    TracePrintf(0, "Init the break tests\n");
    if (*(argv[0]) == '1') {
        void *ptr = malloc(5 * PAGESIZE);
        if (ptr == NULL) {
            TracePrintf(0, "ERROR. UNABLE TO ALLOCATE.\n");
        } else {
            TracePrintf(0, "Malloc Ok. assigned address is %p which is page %u.\n", ptr, (long)ptr >> PAGESHIFT);
        } 
        free(ptr);
        TracePrintf(0, "Free complete...\n");

        ptr = malloc(1000 * PAGESIZE);
        if (ptr != NULL) {
            TracePrintf(0, "ERROR. Should be NULL.\n");
        } 

        ptr = malloc(5 * PAGESIZE);
        if (ptr == NULL) {
            TracePrintf(0, "ERROR. UNABLE TO ALLOCATE.\n");
        } else {
            TracePrintf(0, "Malloc Ok. assigned address is %p which is page %u.\n", ptr, (long)ptr >> PAGESHIFT);
        } 
        free(ptr);

        TracePrintf(0, "Free complete...\n");
        return 0;
    } else if (*(argv[0]) == '2') {
        TracePrintf(0, "This program will do a series of direct calls to Brk. Please verify the internals match what it says was called.\n");
        // TODO find a way to test the freeing of break... cannot think of anything right now besides giving idle a page table 0 and then calling the function explicitly.
        int s = Brk((void *)0x26000);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 1 failed.\n");
        }
        TracePrintf(0, "Break up to 0x25000 called.\n");

        s = Brk((void *)0x23000);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 2 failed.\n");
        }
        TracePrintf(0, "Break down to 0x23000 called.\n");


        s = Brk((void *)0x26000);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 3 failed.\n");
        }
        TracePrintf(0, "Break up to 0x26000 called.\n");

        TracePrintf(0, "Done calling. Please check that the calls worked.");
        Halt();
        return 0;
    } else if (*argv[0] == '3') {
        TracePrintf(0, "Tets that break to address less than mem invalid doesn't work\n");
        int s = Brk((void *)0x14);
        if (s == ERROR) {
            TracePrintf(0, "Test passed.\n");
        } else {
            TracePrintf(0, "Test Failed - expexted error got status %u\n", s);
        }

        return 0;
    } else if (*argv[0] == '4') {
        TracePrintf(0, "Break up to 0x25000 called, then to a slightly misaligned below. SECOND CALL SHOULD NOT CHANGE BRK.\n");
        TracePrintf(0, "Break up to 0x25000 called.\n");
        int s = Brk((void *)0x25000);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 1 failed.\n");
        }
        
        TracePrintf(0, "Break to 0x24900 called.\n");
        s = Brk((void *)0x24900);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 2 failed.\n");
        }
        TracePrintf(0, "Break request should remain the same. Please Verify. Halting....\n");
        // Halt();
        return 0;
        
    } else if (*argv[0] == '5') {
        TracePrintf(0, "Break up to and down to a misaligned address.\n");
        TracePrintf(0, "Break up to 0x25420 called.\n");
        int s = Brk((void *)0x25420);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 1 failed.\n");
        }
        
        TracePrintf(0, "Break to 0x21182 called.\n");
        s = Brk((void *)0x21182);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 2 failed.\n");
        }

        s = Brk((void *)0x27420);
        if (s == ERROR) {
            TracePrintf(0, "ERROR. Call 3 failed.\n");
        }
        Halt();
        return 0;
        
    } else {
        return ERROR;
    }
}
