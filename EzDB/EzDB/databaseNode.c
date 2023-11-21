#include "databaseNode.h"

// CREATE A NODE
KeyValueNode *createNode(char *key, char *value)
{
    KeyValueNode *result = malloc(sizeof(KeyValueNode));
    strcpy(result->value, value);
    strcpy(result->key, key);
    return result;
}

// INSERT NEW NODE INTO NODE LIST
KeyValueNode *insertHead(KeyValueNode **head, KeyValueNode *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}



// Show All - (Print)
void printNode(KeyValueNode *head)
{
    KeyValueNode *temporary = head;
    
    // Base case
    if (temporary == NULL)
    return;
 
    // print the list after head node
    printNode(temporary->next);
 
    // After everything else is printed, print head
    printf("%s %s \n", temporary->key, temporary->value);
}

int lenNode(KeyValueNode *head)
{

    int counter = 0;
    KeyValueNode *temporary = head;

    while (temporary != NULL)
    {
        temporary = temporary->next;
        counter += 1;
    }

    return counter;
}

// Search Query
int findNode(KeyValueNode *head, char *key)
{
    KeyValueNode *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

char *findNodereturnString(KeyValueNode *head, char *key)
{
    KeyValueNode *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return "EMPTY";
}

// delete node
void deleteNode(KeyValueNode **head, char *keys)
{
    KeyValueNode *previous = *head;
    KeyValueNode *current = *head;

    // Check if the head node is the one to be deleted
    if (strcmp(current->key, keys) == 0)
    {
        *head = current->next;
        free(current);
        return;
    }

    // Search for the node to be deleted
    while (current != NULL && strcmp(current->key, keys) != 0)
    {
        previous = current;
        current = current->next;
    }

    // If the key wasn't found in the list
    if (current == NULL)
    {
        printf("Key not found in the list\n");
        return;
    }

    // Delete the node
    previous->next = current->next;
    free(current);
}

// UPDATE
int updateNode(KeyValueNode *head, char *key, char *newvalue)
{
    KeyValueNode *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            strcpy(tmp->value, newvalue);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
