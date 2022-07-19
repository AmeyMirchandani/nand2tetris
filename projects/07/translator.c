#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>
#include "util.h"

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

    DIR* FD = NULL; //directory
    struct dirent* inStruct; //inputfile struct
    FILE* inputFile; //inputfile file descriptor
    FILE* outputFile;
    int done = false;

    if(isPath && ((FD = opendir(argv[1])) == NULL)) //open directory
    {
        printf("Could not open directory: %s\n", argv[1]);
        exit(1);
    }

    //OPEN OUTPUT FILE
    char* outputFileName;
    strcpy(outputFile, argv[1]);
    if(isPath) //if input was a filepath, get the name of the final folder
    {
        outputFileName = getDirName(outputFileName);
    }
    if((outputFile = fopen(outputFileName, "w")) == NULL)
    {
        printf("Could not open output file: %s\n", outputFileName);
        if(isPath)
            closedir(FD);
        exit(1);
    }

    while(!done) //for each FILE
    {
        char* filename; //name of file to open
        strcpy(filename, argv[1]);
        if(isPath) //is a file path
        {
            if((inStruct = readdir(FD)) == NULL) //get next file in directory
            {
                closedir(FD); //no files left in directory
                fclose(outputFile);
                exit(1);
            }
            if(strstr(inStruct->d_name, ".vm") == NULL) //skip file if it does not have the .vm extension
                continue;
            filename = inStruct->d_name;
        }
        if((inputFile = fopen(filename, "r")) == NULL)
        {
            printf("Could not open input file: %s\n", filename);
            if(isPath)
                closedir(FD);
            fclose(outputFile);
            exit(1);
        }
        //PROCESS FILE
        

        if(!isPath) //finish after first file if it is not a directory
            done = true;
    }
}