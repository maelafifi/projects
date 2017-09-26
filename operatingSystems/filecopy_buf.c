#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 16

int main(int argc, char *argv[])
{
    int fd_in, fd_out;
    int count;
    char buf[BUFSIZE];
    
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        printf("Cannot open %s\n", argv[1]);
        exit(1);
    }
    
    fd_out = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd_in < 0) {
        printf("Cannot open %s\n", argv[2]);
        exit(1);
    }
    
    while ((count = read(fd_in, buf, BUFSIZE)) > 0) {
      printf("count = %d\n", count);
      write(fd_out, buf, count);
    }
    
    close(fd_in);
    close(fd_out);

    return 0;
}
