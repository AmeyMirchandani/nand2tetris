#define SUB_TEXT "@SP\nA=A-1\nD=M\nA=A-1\nD=M-D\nM=D\nA=A+1\n"

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
    //get 1st nun and put NOTed version on stack
    decSP(file);
    A_toStackLoc(file);
    fputs("M=!M\n", file);

    //inc sp
    incSP(file);
}

void processFile(FILE* file)
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
    }
}