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


    // FIRST PASS
    LinkedList* symbolTable = initializeDefaultAddresses();
    char line[100]; //line that is read in
    int romAddress = 0;

    while(fgets(line, sizeof(line), inputFile) != NULL)
    {
        char* lineStart = strtok(line, " ");
        if(line[0] == '/' || line[0] == '\n') //if first char is a / or a newline(\n), skip line
            continue;
        else if(lineStart[0] == '@' || lineStart[0] != '(') //if first char is @ or not a (, increment romAddress and skip line
        {
            //printf("Increment Rom ADDRESS: -%s-\n", lineStart);
            romAddress++;
            continue;
        }
        if(lineStart[strlen(lineStart)-1] == '\n') //if last char is a newline, replace it with a NUL char
        {
            lineStart[strlen(lineStart)-1] = 0;
            //printf("Replaced last char with NUL\n");
        }
        
        lineStart[strlen(lineStart)-1] = 0; //remove ending ')'

        //if(romAddress < 40)
            //printf("Rom address: %d\n", romAddress);
        symbolTable = addNode(symbolTable, &lineStart[1], romAddress);
    }

    rewind(inputFile); //reset internal file position pointer for second pass

    // SECOND PASS
    int varAddress = 16; //keeps track of insertion location for variables
    
    while(fgets(line, sizeof(line), inputFile) != NULL) //read lines
    {
        if(line[0] == '/' || line[0] == '\n' || line[0] == '(') //if first char is a / or ( or a newline(\n), skip line
            {
                //printf("// or newline\n");
                continue;
            }
        if(line[strlen(line)-1] == '\n') //if last char is a newline, replace it with a NUL char
            line[strlen(line)-1] = 0;
        //printf("line: -%s-\n", line);

        char outputLine[17]; //line goes here (17th bit is for \0 or NUL bit)

        char* noSpaces = removeStartSpaces(line);
        printf("Line: %s\n", noSpaces);
        if(noSpaces[0] != '@')
        {
            cInsSetup(outputLine); //setup for C Instruction
            if(strchr(line, 'J') == NULL) // dest field exists, dest=comp
            {
                //printf("outputline: -%s-\n", outputLine);
                //char* dest = strtok(line, " =;/"); //dest
                char* dest = strtok(noSpaces, " =;/");
                printf("dest: -%s-\n", dest);
                char* comp = strtok(NULL, " =;/"); //comp
                printf("comp: -%s-\n", comp);
                addComp(outputLine, comp);
                addDest(outputLine, dest);
                addJump(outputLine, NULL);
            }
            else // jmp field exists, comp;jump
            {
                char* comp = strtok(noSpaces, " =;"); //comp
                char* jmp = strtok(NULL, " =;"); //jmp
                addComp(outputLine, comp);
                addDest(outputLine, NULL);
                addJump(outputLine, jmp);
            }
        }
        else // starts with @
        {
            char* noEndSpaces = strtok(noSpaces, " ");
            aInsSetup(outputLine); //setup for A Instruction
            printf("Output Line: %s\n", outputLine);
            if(isdigit(noEndSpaces[1])) // no symbol
            {
                getBinaryStringFromInt(outputLine, atoi(&noEndSpaces[1])); //start after @
            }
            else // symbol
            {
                int address;
                if((address = getAddress(symbolTable, &noEndSpaces[1])) == -1) //not in table
                {
                    //printList(symbolTable);
                    //printf("Adding node: -%s-\n", &noEndSpaces[1]);
                    symbolTable = addNode(symbolTable, &noEndSpaces[1], varAddress); //update symbolTable with new node
                    address = varAddress;
                    varAddress++;
                }
                getBinaryStringFromInt(outputLine, address);
            }
        }

        fputs(outputLine, outputFile);
        fputs("\n", outputFile);
    }
    printList(symbolTable);

    char example[17];
    getBinaryStringFromInt(example, 27058);
    printf("Example: %s\n", example);
    printf("Example[0]: %c\n", example[0]);
    
    freeList(symbolTable);
    fclose(inputFile);
    fclose(outputFile);
}