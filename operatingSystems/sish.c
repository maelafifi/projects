/* sish.c - simple shell */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define MAX_CMD_LEN 512

void read_line(char *line)
{
    char buf[1];
    int i = 0;
    
    while(read(0, buf, 1) > 0) {
        if (buf[0] == '\n') {
            break;
        }

        line[i] = buf[0];
        i = i + 1;

        if (i > (MAX_CMD_LEN - 1)) {
            break;
        }
    }
    line[i] = '\0';

    return;
}

void print_prompt(void)
{
    write(1, "$ ", 2);
}

void exec_command(char *cmd)
{
    pid_t id;
    int exit_code;

    id = fork();

    if (id == 0) {
        /* we are in the child */
        execlp(cmd, cmd, NULL);
        printf("sish: command not found: %s\n", cmd);
        exit(-1);
    } else {
        /* we are in the parent */
        id = wait(&exit_code);
        printf("Child exit_code = %d\n", exit_code);
    }
}

bool process_one_command(void)
{
    bool done = false;
    
    char buf[MAX_CMD_LEN];

    print_prompt();
    read_line(buf);
    printf("cmd: %s\n", buf);
    if (buf[0] == '*') {
        done = true;        
    } else if (buf[0] == 'c') {
        chdir(&(buf[2]));
    } else {
        exec_command(buf);
    }

    return done;
}

int main(int argc, char **argv)
{
    bool done = false;

    while (!done) {
        done = process_one_command();
    }
    
    return 0;
}

