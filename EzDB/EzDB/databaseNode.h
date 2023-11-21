#ifndef databaseNode_h
#define databaseNode_h

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct node
{
    char value[256];
    char key[256];
    struct node *next;
};

typedef struct node KeyValueNode;

KeyValueNode *createNode(char *key, char *value);
KeyValueNode *insertHead(KeyValueNode **head, KeyValueNode *node_to_insert);
void printNode(KeyValueNode *head);
int lenNode(KeyValueNode *head);
int findNode(KeyValueNode *head, char *key);
char *findNodeKey(KeyValueNode *head, char *key);
void deleteNode(KeyValueNode **head, char *keys);
int updateNode(KeyValueNode *head, char *key, char *newvalue);

#endif /* j_node_h */
