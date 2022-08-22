char* getDirName(char* directory) //modifies input string and returns pointer to a character in it
{
    char* prev;
    char* curr;

    prev = strtok(directory, "/");
    curr = strtok(NULL, "/");
    while(curr != NULL)
    {
        prev = curr;
        curr = strtok(NULL, "/");
    }
    return prev;
}

void incSP(FILE* file)
{
    fputs("@SP\nM=M-1\n", file);
}

void decSP(FILE* file)
{
    fputs("@SP\nM=M+1\n", file);
}

void A_toStackLoc(FILE* file)
{
    fputs("@SP\nA=M\n", file);
}

void add(FILE* file)
{
    //get 1st num
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //get 2nd num and put added num onto stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=D+M\n", file);

    //inc sp
    incSP(file);
}

void sub(FILE* file)
{
    //get 1st num
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //get 2nd num and put subtracted num onto stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=M-D", file);

    //inc sp
    incSP(file);
}

void neg(FILE* file)
{
    //get 1st num
    decSP(file);
    A_toStackLoc(file);

    //put negative of number onto stack
    fputs("M=-M\n", file);
    incSP(file);
}

void and(FILE* file)
{
    //get 1st num
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //get 2nd num and put ANDed num onto stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=D&M", file);

    //inc sp
    incSP(file);
}

void or(FILE* file)
{
    //get 1st num
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //get 2nd num and put ORed num onto stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=D|M", file);

    //inc sp
    incSP(file);
}

void not(FILE* file)
{
    //get 1st num and put NOTed version on stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=!M\n", file);

    //inc sp
    incSP(file);
}

void eq(FILE* file, int* boolNum)
{
    //subtract last 2 nums on stack
    sub(file);

    //copy top of stack to D
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //write JEQ instruction -- STACK STILL DECREMENTED
    char instruction[50];

    //@BOOL_boolNum
    sprintf(instruction, "@BOOL_%d\n", boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JEQ\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //inc sp
    incSP(file);

    (*boolNum)++; //increment boolNum
}

void gt(FILE* file, int* boolNum)
{
    //subtract last 2 nums on stack
    sub(file);

    //copy top of stack to D
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //write JEQ instruction -- STACK STILL DECREMENTED
    char instruction[50];

    //@BOOL_boolNum
    sprintf(instruction, "@BOOL_%d\n", boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JGT\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //inc sp
    incSP(file);

    (*boolNum)++; //increment boolNum
}

void lt(FILE* file, int* boolNum)
{
    //subtract last 2 nums on stack
    sub(file);

    //copy top of stack to D
    decSP(file);
    A_toStackLoc(file);
    fputs("D=M\n", file);

    //write JEQ instruction -- STACK STILL DECREMENTED
    char instruction[50];

    //@BOOL_boolNum
    sprintf(instruction, "@BOOL_%d\n", boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JLT\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", boolNum);
    fputs(instruction, file);

    //inc sp
    incSP(file);

    (*boolNum)++; //increment boolNum
}

void push(FILE* file, char* pushType)
{
    char* third = strtok(NULL, " /"); //third word

    if(strcmp(pushType, "constant")) //push constant [num]
    {
        int num = atoi(third); //number to push
        char line[50];
        sprintf(line, "@%d\n", num); //put the number to be pushed into the A register

        fputs("D=A\n", file); //copy number to be pushed from the A register to the D register

        A_toStackLoc(file);
        fputs("M=D\n", file); //copy number to be pushed from the D register onto the stack location in the HEAP

        incSP(file); //inc sp
    }
}

void processFile(FILE* file, int* boolNum)
{
    char line[100]; //line to read in input

    while(fgets(line, sizeof(line), file) != NULL) //read all lines from file
    {
        if(line[0] == '/' || line[0] == '\n') //if first char is a / or a newline(\n), skip line
            continue;

        char* first = strtok(line, " /"); //first word
        if(strcmp(first, "add") == 0) // add
        {
            add(file);
        }
        else if(strcmp(first, "sub") == 0) // subtract
        {
            sub(file);
        }
        else if(strcmp(first, "neg") == 0) // negative
        {
            neg(file);
        }
        else if(strcmp(first, "and") == 0) // and
        {
            and(file);
        }
        else if(strcmp(first, "or") == 0) // or
        {
            or(file);
        }
        else if(strcmp(first, "not") == 0) // not
        {
            not(file);
        }
        else if(strcmp(first, "eq") == 0) // eq
        {
            eq(file, boolNum);
        }
        else if(strcmp(first, "gt") == 0) // gt
        {
            gt(file, boolNum);
        }
        else if(strcmp(first, "lt") == 0) // lt
        {
            lt(file, boolNum);
        }
        else if(strcmp(first, "push") == 0) //ALL PUSH COMMANDS
        {
            char* second = strtok(NULL, " /"); //second word
            push(file, second);
        }
    }
}