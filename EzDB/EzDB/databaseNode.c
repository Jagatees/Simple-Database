#include "databaseNode.h"

KeyValueNode *createNode(char *key, char *value)
{
    KeyValueNode *result = malloc(sizeof(KeyValueNode));
    strcpy(result->value, value);
    strcpy(result->key, key);
    return result;
}

KeyValueNode *insertHead(KeyValueNode **head, KeyValueNode *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}



void printNode(KeyValueNode *head)
{
    KeyValueNode *temporary = head;

    // version older
    while (temporary != NULL)
    {
        printf("%s %s \n", temporary->key, temporary->value);
        temporary = temporary->next;
    }
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

void deleteNode(KeyValueNode **head, char *keys)
{
    KeyValueNode *previous = *head;
    KeyValueNode *current = *head;

    if (strcmp(current->key, keys) == 0)
    {
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL && strcmp(current->key, keys) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Key not found in the list\n");
        return;
    }

    previous->next = current->next;
    free(current);
}

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
