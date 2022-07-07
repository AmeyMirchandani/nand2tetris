#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Assembler <filename>");
        exit(1);
    }
    
    // OPEN INPUT FILE
    FILE *inputFile = fopen(argv[1], "r");
    if(inputFile == NULL)
        printf("No file with that name found");
    else
        printf("Succesfully opened input file\n");

    // FORMAT OUTPUT FILE NAME
    char outputFileName[strlen(argv[1])+1]; //+1 for \0
    strcpy(outputFileName, argv[1]); //now has inputFileName
    char* front = strtok(outputFileName, "."); //split on . to get part before .
    char dotHack[6]; //.hack\0
    strcpy(dotHack, ".hack");
    strcat(front, dotHack); //put .hack after Inputfilename

    // OPEN OUTPUT FILE
    FILE *outputFile = fopen(front, "w");
    if(outputFile == NULL)
        printf("Failed to create/open output file");
    else
        printf("Succesfully opened output file");

    char line[60];
    while(fgets(line, sizeof(line), inputFile) != NULL)
    {

    }

    fclose(inputFile);
}