#ifndef CODES_H
#define CODES_H
#include <string.h>
#include <ctype.h>

void cInsSetup(char* line)
{
    strcpy(line, "111");
}

void aInsSetup(char* line)
{
    strcpy(line, "0");
}

void getBinaryStringFromInt(char* line, int num)
{
    /*
    line[17] = 0; //set NUL byte

    int i = 16;
    while(num > 0)
    {
        line[i] = num % 2;
        i++;
        num /= 2;
    }
    while(i > 0)
    {
        line[i] = '0';
    }
    */
   char convertedInt[16]; //up to 15 bytes long
   itoa(num, convertedInt, 2);

   char newline[16]; //15 bytes long
   for(int i = 0; i < 15 - strlen(convertedInt); i++)
   {
        newline[i] = '0';
        newline[i+1] = 0;
   } 

   strcat(newline, convertedInt);
   strcat(line, newline);
}

void addDest(char* line, char* code)
{
    if(code == NULL) //NULL
    {
        strcat(line, "000");
        return;
    }

    if(strchr(code, 'A') != NULL) //A
        strcat(line, "1");
    else
        strcat(line, "0");
    
    if(strchr(code, 'D') != NULL) //D
        strcat(line, "1");
    else
        strcat(line, "0");

    if(strchr(code, 'M') != NULL) //M
        strcat(line, "1");
    else
        strcat(line, "0");
}

void addJump(char* line, char* code)
{
    if(code == NULL) //NULL
    {
        strcat(line, "000");
        return;
    }

    if(strstr(code, "GT") != NULL) //JGT
        strcat(line, "001");
    else if(strstr(code, "EQ") != NULL) //JEQ
        strcat(line, "010");
    else if(strstr(code, "GE") != NULL) //JGE
        strcat(line, "011");
    else if(strstr(code, "LT") != NULL) //JLT
        strcat(line, "100");
    else if(strstr(code, "NE") != NULL) //JNE
        strcat(line, "101");
    else if(strstr(code, "LE") != NULL) //JLE
        strcat(line, "110");
    else if(strstr(code, "MP") != NULL) //JMP
        strcat(line, "111");
}

void addComp(char* line, char* code)
{
    if(strchr(code, 'M') != NULL) //if uses M, set a to 1
        strcat(line, "1");
    else
        strcat(line, "0"); //else if doesn't use M, set a to 0
    
    if(strlen(code) == 1) //code length of 1
    {
        switch (code[0])
        {
        case '0':
            strcat(line, "101010");
            break;
        case '1':
            strcat(line, "111111");
            break;
        case 'D':
            strcat(line, "001100");
            break;
        case 'A':
        case 'M':
            strcat(line, "110000");
            break;
        
        default:
            break;
        }
    }
    else if(strlen(code) == 2) //code length of 2
    {
        if(strcmp(code, "-1") == 0) //-1
            strcat(line, "111010");
        else if(strcmp(code, "!D") == 0) //!D
            strcat(line, "001101");
        else if(strcmp(code, "!A") == 0 || strcmp(code, "!M") == 0) //!A OR !M
            strcat(line, "110001");
        else if(strcmp(code, "-D") == 0) //-D
            strcat(line, "001111");
        else if(strcmp(code, "-A") == 0 || strcmp(code, "-M") == 0) //-A OR -M
            strcat(line, "110011");
    }
    else //code length of 3
    {
        if(strcmp(code, "D+1") == 0) //D+1
            strcat(line, "011111");
        else if(strcmp(code, "A+1") == 0 || strcmp(code, "M+1") == 0) //A+1 OR M+1
            strcat(line, "110111");
        else if(strcmp(code, "D-1") == 0) //D-1
            strcat(line, "001110");
        else if(strcmp(code, "A-1") == 0 || strcmp(code, "M-1") == 0) //A-1 OR M-1
            strcat(line, "110010");
        else if(strcmp(code, "D+A") == 0 || strcmp(code, "D+M") == 0) //D+A OR D+M
            strcat(line, "000010");
        else if(strcmp(code, "D-A") == 0 || strcmp(code, "D-M") == 0) //D-A OR D-M
            strcat(line, "010011");
        else if(strcmp(code, "A-D") == 0 || strcmp(code, "M-D") == 0) //A-D OR M-D
            strcat(line, "000111");
        else if(strcmp(code, "D&A") == 0 || strcmp(code, "D&M") == 0) //D&A OR D&M
            strcat(line, "000000");
        else if(strcmp(code, "D|A") == 0 || strcmp(code, "D|M") == 0) //D|A OR D|M
            strcat(line, "010101");
    }
}

#endif