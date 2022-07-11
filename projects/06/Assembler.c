#include <stdio.h>
#include <stdlib.h>
#include "Codes.h"
#include "LinkedList.h"

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
    {
        printf("No file with that name found");
        exit(1);
    }
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
    {
        printf("Failed to create/open output file");
        exit(1);
    }
    else
        printf("Succesfully opened output file\n");


    LinkedList* symbolTable = initializeDefaultAddresses();

    // SECOND PASS
    char line[100]; //line that is read in
    //int varAddress = 16; //keeps track of insertion location for variables
    
    while(fgets(line, sizeof(line), inputFile) != NULL) //read lines
    {
        if(line[0] == '/' || line[0] == '\n' || line[0] == '(') //if first char is a / or ( or a newline(\n), skip line
            {
                printf("// or newline\n");
                continue;
            }
        if(line[strlen(line)-1] == '\n') //if last char is a newline, replace it with a NUL char
            line[strlen(line)-1] = 0;
        printf("line: -%s-\n", line);

        char outputLine[17]; //line goes here (17th bit is for \0 or NUL bit)

        if(line[0] != '@')
        {
            cInsSetup(outputLine); //setup for C Instruction
            if(strchr(line, 'J') == NULL) // dest field exists, dest=comp
            {
                printf("outputline: -%s-\n", outputLine);
                char* dest = strtok(line, "=;"); //dest
                printf("dest: -%s-\n", dest);
                char* comp = strtok(NULL, "=;"); //comp
                printf("comp: -%s-\n", comp);
                addComp(outputLine, comp);
                addDest(outputLine, dest);
                addJump(outputLine, NULL);
            }
            else // jmp field exists, comp;jump
            {
                char* comp = strtok(line, "=;"); //comp
                char* jmp = strtok(NULL, "=;"); //jmp
                addComp(outputLine, comp);
                addDest(outputLine, NULL);
                addJump(outputLine, jmp);
            }
        }
        else
        {
            aInsSetup(outputLine); //setup for A Instruction
            if(isdigit(line[1])) // no symbol
            {
                getBinaryStringFromInt(outputLine, atoi(&line[1])); //start after @
            }
            else // symbol
            {
                
            }
        }

        fputs(outputLine, outputFile);
        fputs("\n", outputFile);
    }

    freeList(symbolTable);
    fclose(inputFile);
    fclose(outputFile);
}