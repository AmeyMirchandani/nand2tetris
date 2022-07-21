#define ADD_TEXT "@SP\nA=A-1\nD=M\nA=A-1\nD=D+M\nM=D\nA=A+1\n"

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

void add(FILE* file)
{
    fputs(ADD_TEXT, file);
}

void processFile(FILE* file)
{
    char line[100]; //line to read in input

    while(fgets(line, sizeof(line), file) != NULL)
    {
        if(line[0] == '/' || line[0] == '\n') //if first char is a / or a newline(\n), skip line
            continue;
        
        char* first = strtok(line, " /"); //first word
        if(strcmp(first, "add") == 0) // add
        {
            add(file); //put assembly commands to add 2 numbers from stack into output file
            continue;
        }
    }
}