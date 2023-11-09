//
//  j_node.h
//  EzDB
//
//  Created by Jagateesvaran on 28/10/23.
//

#ifndef j_node_h
#define j_node_h

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

typedef struct node node_t;

node_t *createNode(char *key, char *value);
node_t *insertHead(node_t **head, node_t *node_to_insert);
void printNode(node_t *head);
int lenNode(node_t *head);
int findNode(node_t *head, char *key);
char *findNodereturnString(node_t *head, char *key);
void deleteNode(node_t **head, char *keys);
int updateNode(node_t *head, char *key, char *newvalue);

#endif /* j_node_h */
