#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN_LEN 64

/* This struct is used to pass information between functions. */
struct grep_info {
    char pattern[MAX_PATTERN_LEN];
    char **files;
};

void print_usage(void)
{
    printf("Usage: usfgrep <pattern> <file1> [<file2> ...]\n");
    return;
}

void parse_args(int argc, char **argv, struct grep_info *gi)
{
    if (argc < 3) {
        printf("Insufficient arguments.\n");
        print_usage();
        exit(-1);
    }

    strcpy(gi->pattern, argv[1]);
    gi->files = argv + 2;
    
    return;
}

/* Get a line from a file referenced by fd. Put data into the provided line string. */
int get_line(int fd, char *line)
{
    return 0;
}

/* Grep a line from the file reference by fd. */
void grep_line(int fd)
{
    /* Call get_line(fd, line) to get a line from the file. */

    return;
}

/* Grep a single file. */
void grep_file(char *file)
{
    /* Open file */

    /* Loop through file and grep each line */

    /* Call grep line */
    
    /* Close file */

    return;
}

/* Grep all files provided on the command line. */
void grep_files(struct grep_info *gi)
{
    int i = 0;
    char *file;

    while (true) {
        file = gi->files[i];
        if (file == NULL) {
            break;
        }

        printf("file: %s\n", file);

        grep_file(file);
        
        i = i + 1;
    }

    return;
}

int main(int argc, char **argv)
{
    struct grep_info gi;
    
    parse_args(argc, argv, &gi);

    grep_files(&gi);

    return 0;
}
