#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* A struct used to package to return values */
struct results {
    int min;
    int max;
    int bytes;
    int spaces;
};

struct line_results {
    int len;
    int bytes;
    int spaces;
};

/* Open a file, check for errors, return a valid fd */
int open_file(char *filename) {
    int fd;

    fd = open(filename, O_RDONLY);

    if (fd < 0) {
        printf("Cannot open %s, exiting.\n", filename);
        exit(-1);
    }
    
    return fd;
}

/* Read a line and return it's length. Return -1 if no more lines. */
struct line_results read_line(int fd) {
    char buf[1];
    int rv;
    int len = 0;
    int bytes = 0;
    int spaces = 0;
    
    struct line_results r;
    r.len = 0;
    r.bytes = 0;
    r.spaces = 0;
    
    while ((rv = read(fd, buf, 1)) > 0) {
        bytes += 1;

        if (buf[0] == ' ') {
            spaces += 1;
        }
        
        /* Check for newline */
        if (buf[0] == '\n') {
            break;
        }
        len = len + 1;
    }

    /* Check if we are at the end of the file. */
    if ((rv == 0) && (len == 0)) {
        len = -1;
    }

    r.len = len;
    r.bytes = bytes;
    r.spaces = spaces;
    
    return r;
}

/* Analyze all the lines in a file and return the min and max lengths. */
struct results analyze_file(int fd) {
    struct results r;
    int len = 0;
    r.min = 0;
    r.max = 0;
    r.bytes = 0;
    r.spaces = 0;
    struct line_results lr;

    /* Read the first line, if it exists, to get initial min and max values. */
    lr = read_line(fd);
    len = lr.len;
    r.bytes += lr.bytes;
    r.spaces += lr.spaces;
    
    if (len >= 0) {
        r.min = len;
        r.max = len;
    } else {
        return r;
    }

    while (true) {
        lr = read_line(fd);
        len = lr.len;
        r.bytes += lr.bytes;
        r.spaces += lr.spaces;

        if (len < 0) {
            break;
        }

        /* Update min and max values. */
        if (len < r.min) {
            r.min = len;
        }
        if (len > r.max) {
            r.max = len;
        }
    }
    
    return r;
}

/* Print min and max vales from a struct results value. */
void print_results(struct results r)
{
    printf("min    = %d\n", r.min);
    printf("max    = %d\n", r.max);
    printf("bytes  = %d\n", r.bytes);
    printf("spaces = %d\n", r.spaces);

    return;
}
    
int main(int argc, char **argv)
{
    int fd;
    struct results r;
    
    /* check command line arguments */
    
    /* open the file */
    fd = open_file(argv[1]);
    
    /* analyze lines */
    r = analyze_file(fd);

    /* print results */
    print_results(r);

    /* close file */
    close(fd);
   
    return 0;
}
