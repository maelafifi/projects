#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    char buf[1];
    
    while (read(0, buf, 1) > 0) {
        printf("%c", buf[0]);
    }

    return 0;
}
