#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct LinkedList
{
    char name[30];
    int address;
    struct LinkedList *next;
};
#define LinkedList struct LinkedList

LinkedList* createNode(char* name, int address)
{
    LinkedList* newNode = malloc(sizeof(LinkedList));
    newNode->address = address;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

LinkedList* addNode(LinkedList* list, char* name, int address)
{
    if(list == NULL)
        return createNode(name, address);

    LinkedList* newNode = createNode(name, address);
    newNode->next = list;
    return newNode;
}

int getAddress(LinkedList* list, char* name)
{
    LinkedList* currentNode = list;
    while(currentNode != NULL)
    {
        if(strcmp(name, currentNode->name) == 0)
            return currentNode->address;
        
        currentNode = currentNode->next;
    }
    return -1;
}

void freeList(LinkedList* list)
{
    while(list != NULL)
    {
        LinkedList* nextNode = list->next;
        free(list);
        list = nextNode;
    }
}

void printList(LinkedList* list)
{
    LinkedList* currentNode = list;
    while(currentNode != NULL)
    {
        printf("Name: %s, Address: %d\n", currentNode->name, currentNode->address);
        currentNode = currentNode->next;
    }
}

LinkedList* initializeDefaultAddresses()
{
    LinkedList* list = createNode("SP", 0);
    list = addNode(list, "R0", 0);
    list = addNode(list, "LCL", 1);
    list = addNode(list, "R1", 1);
    list = addNode(list, "ARG", 2);
    list = addNode(list, "R2", 2);
    list = addNode(list, "THIS", 3);
    list = addNode(list, "R3", 3);
    list = addNode(list, "THAT", 4);
    list = addNode(list, "R4", 4);
    list = addNode(list, "R5", 5);
    list = addNode(list, "R6", 6);
    list = addNode(list, "R7", 7);
    list = addNode(list, "R8", 8);
    list = addNode(list, "R9", 9);
    list = addNode(list, "R10", 10);
    list = addNode(list, "R11", 11);
    list = addNode(list, "R12", 12);
    list = addNode(list, "R13", 13);
    list = addNode(list, "R14", 14);
    list = addNode(list, "R15", 15);
    list = addNode(list, "SCREEN", 16384);
    list = addNode(list, "KBD", 24576);
    return list;
}

#endif