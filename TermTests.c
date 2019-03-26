#include <stdio.h>
#include <stdlib.h>
#include <comp421/yalnix.h>

int main(int argc, char **argv) {
    printf("Init the term tests\n");

    if (*argv[0] == '1') {
        char string[] = "abcdefghijklmnopqrstuvwxyz\n";
        int length = sizeof(string) - 1;

        Fork();

        int num_chars = TtyWrite(1, string, length);
        int pid = GetPid();

        if (num_chars == length) {
            printf("\nPASSED TEST: Process %u successfully wrote %u chars to terminal 1\n", pid, num_chars);
        } else {
            printf("\nFAILED TEST: Process %u wrote %u chars to terminal 1 insead of %u\n", pid, num_chars, length);
        
        }

        return 0;
    } else if (*argv[0] == '2') {
        int length = 10; // >:)
        char str[length];

        Fork();

        int num_chars = TtyRead(1, str, length);
        int pid = GetPid();

        printf("\n Process %u successfully read %u chars from terminal\n", pid, num_chars);

        return 0;
    } else if (*argv[0] == '3') {
        char string[] = "Please wait 1-2 seconds then type 123\\n into this terminal now..\n";
        int length = sizeof(string) - 1;
        char string2[] = "Please wait 1-2 seconds then type 123\\n into this terminal AGAIN\n";
        int length2 = sizeof(string2) - 1;
        
        int str_len = 10;
        char str[str_len];

        printf("This test will ask you wait 1-2 seconds then to type '123' into terminal 1 and 2.\n");
        int num_chars;
        num_chars = TtyWrite(1, string, length);

        int x = Fork();
        if (x == 0) {
            num_chars = TtyRead(1, str, str_len);
            printf("The read call has completed. Attempting to write to terminal 2.");
            num_chars = TtyWrite(2, string, length); // z is waiting on this term
            return 1;
        }
        int y = Fork();
        if (y == 0) {
            Delay(2);
            num_chars = TtyRead(1, str, str_len);
            return 2;
        }
        int z = Fork();
        if (z == 0) {
            num_chars = TtyRead(2, str, str_len);
            num_chars = TtyWrite(2, string2, length2); // w is waiting on this term
            return 3;
        }

        int w = Fork();
        if (w == 0) {
            Delay(2);
            num_chars = TtyRead(2, str, str_len);
            num_chars = TtyWrite(1, string2, length2); // y is waiting on this term
            return 4;
        }
        
        int pid, status;
        pid = Wait(&status);
        if (pid != x && status != 1) {
            printf("Test 1 Failed. Here is num chars so i dont get warnings %u\n", num_chars);
        } else {
            printf("Test 1 success\n");
        }

        pid = Wait(&status);
        if (pid != z && status != 3) {
            printf("Test 2 Failed\n");
        } else {
            printf("Test 2 success\n");
        }

        pid = Wait(&status);
        if (pid != w && status != 4) {
            printf("Test 3 Failed\n");
        } else {
            printf("Test 3 success\n");
        }

        pid = Wait(&status);
        if (pid != y && status != 2) {
            printf("Test 4 Failed\n");
        } else {
            printf("Test 4 success\n");
        }

        pid = Wait(&status);
        if (pid != ERROR && status != 2) {
            // This status should be unchanged and have the value of 2.
            printf("Test 5 Failed\n");
        } else {
            printf("Test 5 success\n");
        }

        printf("Tests complete.\n");
        return 5;
    } else if (*argv[0] == '4') {
        // TODO write a test that does reads AFTER the data has been put in (use delay)
        char string2[] = "Please wait 1-2 seconds then type 1234567\\nabc\\nabc\\nabc\\n into this terminal\n";
        int length2 = sizeof(string2) - 1;
        int num_chars;
        int pid = GetPid();


        num_chars = TtyWrite(1, string2, length2);

        Delay(30);

        int str_len = 5;
        char str[str_len];
        num_chars = TtyRead(1, str, str_len); // 12345
        printf("\nProcess %u successfully read %u chars from terminal\n", pid, num_chars);
        if (str[0] != '1' || str[1] != '2' || str[2] != '3' || str[3] != '4' || str[4] != '5') {
            printf("FAILURE\n");
            return ERROR;
        }

        num_chars = TtyRead(1, str, str_len); // 67\n
        printf("\nProcess %u successfully read %u chars from terminal\n", pid, num_chars);
        if (str[0] != '6' || str[1] != '7' || str[2] != '\n') {
            printf("FAILURE\n");
            return ERROR;
        }
        num_chars = TtyRead(1, str, str_len); // abc\n
        printf("\nProcess %u successfully read %u chars from terminal\n", pid, num_chars);
        if (str[0] != 'a' || str[1] != 'b' || str[2] != 'c' || str[3] != '\n') {
            printf("FAILURE\n");
            return ERROR;
        }

        num_chars = TtyRead(1, str, str_len); // abc\n
        printf("\nProcess %u successfully read %u chars from terminal\n", pid, num_chars);
        if (str[0] != 'a' || str[1] != 'b' || str[2] != 'c' || str[3] != '\n') {
            printf("FAILURE\n");
            return ERROR;
        }

        num_chars = TtyRead(1, str, str_len); // abc\n
        if (str[0] != 'a' || str[1] != 'b' || str[2] != 'c' || str[3] != '\n') {
            printf("FAILURE\n");
            return ERROR;
        }


    }

    return 0;
}