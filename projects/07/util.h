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