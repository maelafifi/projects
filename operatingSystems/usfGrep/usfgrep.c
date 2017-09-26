#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// colors for colorization of output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *word; // stores query word
char *file; //stores current file we are searching through
int lineCount = 0; // stores current line that we are reading from a particular file
int argumentCount = 0; // number of arguments (Is argsc global?)

// prints line, line number, and filename where query word is found
void printLine(int lineCount, int counter, char line[])
{
    int i;

    if(argumentCount > 3) // output for multiple files
    {
        printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET, file);
        printf(ANSI_COLOR_RED "%d: " ANSI_COLOR_RESET, lineCount);
        for(i = 0; i < counter; i++)
        {
            printf(ANSI_COLOR_CYAN "%c" ANSI_COLOR_RESET, line[i]);
        }
    }
    else // output for only one file
    {
        printf(ANSI_COLOR_RED "%d: "ANSI_COLOR_RESET, lineCount);
        for(i = 0; i < counter; i++)
        {
            printf(ANSI_COLOR_CYAN"%c"ANSI_COLOR_RESET, line[i]);
        }
    }
    printf("\n");
    return;
}

// Search for word in a given line from a given file
void searchLine(char line[], char word[], int count)
{
    int lineIndex = 0; 
    int wordIndex = 0;
    int indexHolder;

    while(lineIndex < count)
    {
        while((line[lineIndex] != word[0]) && (lineIndex < count))
        {
            lineIndex++;
        }

        indexHolder = lineIndex;

        while (line[lineIndex] == word[wordIndex] && lineIndex < count && word[wordIndex] != '\0') 
        {
           lineIndex++;
           wordIndex++;
        }

        if(word[wordIndex] == '\0')
        {
            printLine(lineCount, count, line);
            return;
        }

        lineIndex = indexHolder + 1;
        wordIndex = 0;
    }
    return;
}

// Read each line from a given file
int readLine(int fd)
{
    int end = 0;
    char buf[1];
    int rv;
    char line[511];
    int count = 0;
    int search = 0;
    

    while((rv = read(fd, buf, 1)) > 0)
    {
        if(buf[0] == '\n')
        {
            lineCount++;
            break;
        }
        else
        {
            line[count] = buf[0];
            count++;

            if(count > 511)
            {
                printf("Maximum characters for a single line in file; exiting.\n");
                exit(-1);
            }
        }
    }

    if(count > 0 && rv == 0)
    {
        end = -1;
        lineCount++;
    }

    if(count == 0 && rv == 0)
    {
        end = -1;
    }

    searchLine(line, word, count);

    return end;
}

// Reads particular file until EOF
void readFile(int fd)
{
    int end;
    
    while((end = readLine(fd)) >= 0)
    {
        ;
    }
    
    return;
    
}


int main(int argc, char **argv)
{
    int fd;
    word = argv[1];
    argumentCount = argc;
    int i;

    if(argc < 3)
    {
        printf("Error: Insufficient Arguments\nUsage: usfgrep <string> <file1> [<file2> ...]\n");
    }

    for(i = 2; i < argc; i++)
    {
        file = argv[i]; // store filename
        lineCount = 0; // initialize line count for this particular file
        fd = open(file, O_RDONLY); // open file

        if (fd < 0)
        {
            printf("Cannot open %s. Next file.\n", file);
        }
        else
        {
            readFile(fd);
        }
    }

    close(fd);
    return 0;
}