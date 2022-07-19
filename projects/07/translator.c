#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>

#define true 1
#define false 0

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("translator <filename/path>");
        exit(1);
    }

    //CHECK IF INPUT IS A PATH OR A FILE
    int isPath = (strchr(argv[1], '.') == NULL); //if no . then input was a path (no filename extension)

    
}