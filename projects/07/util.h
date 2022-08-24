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
    fputs("@SP\nM=M+1\n", file);
}

void decSP(FILE* file)
{
    fputs("@SP\nM=M-1\n", file);
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
    sprintf(instruction, "@BOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JEQ\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", *boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", *boolNum);
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
    sprintf(instruction, "@BOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JGT\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", *boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", *boolNum);
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
    sprintf(instruction, "@BOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //JEQ
    fputs("D;JLT\n", file);

    //put 0 on stack
    A_toStackLoc(file);
    fputs("M=0\n", file);

    //@ENDBOOL_boolNum
    sprintf(instruction, "@ENDBOOL_%d\n", *boolNum);
    fputs(instruction, file);

    //Jump to end of sequence
    fputs("0;JMP\n", file);

    //(BOOL_boolNum)
    sprintf(instruction, "(BOOL_%d)\n", *boolNum);
    fputs(instruction, file);

    //put -1 on stack
    A_toStackLoc(file);
    fputs("M=-1\n", file);

    //(ENDBOOL_boolNum)
    sprintf(instruction, "(ENDBOOL_%d)\n", *boolNum);
    fputs(instruction, file);

    //inc sp
    incSP(file);

    (*boolNum)++; //increment boolNum
}

void push(FILE* file, char* pushType, char* fileName)
{
    char* third = strtok(NULL, " /\n"); //third word

    if(strcmp(pushType, "constant") == 0) //push constant [num]
    {
        int num = atoi(third); //number to push
        char line[50];
        sprintf(line, "@%d\n", num); //put the number to be pushed into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy number to be pushed from the A register to the D register

        A_toStackLoc(file);
        fputs("M=D\n", file); //copy number to be pushed from the D register onto the stack location in the HEAP

        incSP(file); //inc sp
    }
    else if(strcmp(pushType, "local") == 0) //push local [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@LCL\nA=M\n", file); //put address of local segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "argument") == 0) //push argument [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@ARG\nA=M\n", file); //put address of argument segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "this") == 0) //push this [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@THIS\nA=M\n", file); //put address of this segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "that") == 0) //push that [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@THAT\nA=M\n", file); //put address of that segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "pointer") == 0) //push pointer [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@3\n", file); //put address of pointer segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "temp") == 0) //push temp [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@5\n", file); //put address of temp segment in heap into A register

        fputs("A=D+A\n", file); //put address to be pushed from into A register, calculated using offset

        fputs("D=M\n", file); //get value of local segment in heap, including the offset, then put it into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of local including offset (which is in D register)

        incSP(file);
    }
    else if(strcmp(pushType, "static") == 0) //push static [num]
    {
        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%s.%d\n", fileName, offset); //put the address of variable [fileName].[offset] into the A register
        fputs(line, file);

        fputs("D=M\n", file); //put value of the [fileName].[offset] variable in memory into D register

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("M=D\n", file); //set top of stack to value of [fileName].[offset] variable in memory (from D register)

        incSP(file);
    }
}

void pop(FILE* file, char* pushType, char* fileName)
{
    char* third = strtok(NULL, " /\n"); //third word

    if(strcmp(pushType, "local") == 0) //pop local [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@LCL\nA=M\n", file); //put address of local segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "argument") == 0) //pop argument [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@ARG\nA=M\n", file); //put address of argument segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "this") == 0) //pop this [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@THIS\nA=M\n", file); //put address of this segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "that") == 0) //pop that [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@THAT\nA=M\n", file); //put address of that segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "pointer") == 0) //pop pointer [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@3\n", file); //put address of pointer segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "temp") == 0) //pop temp [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%d\n", offset); //put the offset into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy offset from the A register to the D register

        fputs("@5\n", file); //put address of temp segment in heap into A register

        fputs("D=D+A\n", file); //put address to be popped into, to D register, calculated using offset

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold address to pop into

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to address to pop into

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
    else if(strcmp(pushType, "static") == 0) //pop static [num]
    {
        decSP(file); //dec sp

        A_toStackLoc(file); //set A to location in heap of stack

        fputs("D=M\n", file); //put value of top of stack into D register
        
        fputs("@13\nM=D\n", file); //set general purpose register #13 to hold value of top of stack

        int offset = atoi(third); //offset
        char line[50];
        sprintf(line, "@%s.%d\n", fileName, offset); //put the address of variable [fileName].[offset] into the A register
        fputs(line, file);

        fputs("D=A\n", file); //copy the address of variable [fileName].[offset] from the A register to the D register

        fputs("@14\nM=D\n", file); //set general purpose register #14 to hold the address of variable [fileName].[offset]

        fputs("@13\nD=M\n", file); //move value on top of stack to D register

        fputs("@14\nA=M\n", file); //set A register to the address of variable [fileName].[offset]

        fputs("M=D\n", file); //set address to pop into to top of stack
    }
}

void processFile(FILE* file, FILE* outputFile, char* noExtensionFileName, int* boolNum)
{
    char line[100]; //line to read in input

    while(fgets(line, sizeof(line), file) != NULL) //read all lines from file
    {
        if(line[0] == '/' || line[0] == '\n') //if first char is a / or a newline(\n), skip line
            continue;

        char* first = strtok(line, " /\n"); //first word
        
        if(strcmp(first, "add") == 0) // add
        {
            add(outputFile);
        }
        else if(strcmp(first, "sub") == 0) // subtract
        {
            sub(outputFile);
        }
        else if(strcmp(first, "neg") == 0) // negative
        {
            neg(outputFile);
        }
        else if(strcmp(first, "and") == 0) // and
        {
            and(outputFile);
        }
        else if(strcmp(first, "or") == 0) // or
        {
            or(outputFile);
        }
        else if(strcmp(first, "not") == 0) // not
        {
            not(outputFile);
        }
        else if(strcmp(first, "eq") == 0) // eq
        {
            eq(outputFile, boolNum);
        }
        else if(strcmp(first, "gt") == 0) // gt
        {
            gt(outputFile, boolNum);
        }
        else if(strcmp(first, "lt") == 0) // lt
        {
            lt(outputFile, boolNum);
        }
        else if(strcmp(first, "push") == 0) //ALL PUSH COMMANDS
        {
            char* second = strtok(NULL, " /"); //second word
            push(outputFile, second, noExtensionFileName);
        }
        else if(strcmp(first, "pop") == 0) //ALL POP COMMANDS
        {
            char* second = strtok(NULL, " /"); //second word
            pop(outputFile, second, noExtensionFileName);
        }
    }
}