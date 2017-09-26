/* args.c - demonstrate command-line processing */

#include <stdio.h>  /* Standard C header file with prototypes and  */
                    /* constants for basic input/output functions */
                    /* (e.g., printf)                              */

int main(int argc, char *argv[])
{
    /* All variable declarations must go at the top of a function */
    /* declaration, even variables for loops */

    int i;

    printf("argc = %d\n", argc);

    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    /* return exit code to shell */
    return 0;
}

