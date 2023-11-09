#include "j_node.h"

// CREATE A NODE
node_t *createNode(char *key, char *value)
{
    node_t *result = malloc(sizeof(node_t));
    strcpy(result->value, value);
    strcpy(result->key, key);
    return result;
}

// INSERT NEW NODE INTO NODE LIST
node_t *insertHead(node_t **head, node_t *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

// Show All - (Print)
void printNode(node_t *head)
{
    node_t *temporary = head;

    while (temporary != NULL)
    {
        printf("%s %s \n", temporary->key, temporary->value);
        temporary = temporary->next;
    }
}

int lenNode(node_t *head)
{

    int counter = 0;
    node_t *temporary = head;

    while (temporary != NULL)
    {
        temporary = temporary->next;
        counter += 1;
    }

    return counter;
}

// Search Query
int findNode(node_t *head, char *key)
{
    node_t *tmp = head;
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

char *findNodereturnString(node_t *head, char *key)
{
    node_t *tmp = head;
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
void deleteNode(node_t **head, char *keys)
{
    node_t *previous = *head;
    node_t *current = *head;

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
int updateNode(node_t *head, char *key, char *newvalue)
{
    node_t *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            printf("Updated key \"%s\" with new value \n", tmp->value);
            strcpy(tmp->value, newvalue);
            printf("Updated key \"%s\" with new value \n", tmp->value);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
