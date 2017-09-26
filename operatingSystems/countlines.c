#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd_in;
  int count;
  int line_count = 0;
  char buf[1];
    
  fd_in = open(argv[1], O_RDONLY);
  if (fd_in < 0) {
    printf("Cannot open %s\n", argv[1]);
    exit(1);
  }
    
  while ((count = read(fd_in, buf, 1)) > 0) {
    if (buf[0] == '\n') {
      printf("FOUND newline\n");
      line_count += 1;
    }
  }
    
  close(fd_in);

  printf("line_count = %d\n", line_count);
  
  return 0;
}
