#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char buf[1];
    
    printf("$ ");
    fflush(stdout);
    read(0, buf, 1);

    return 0;
}
    
