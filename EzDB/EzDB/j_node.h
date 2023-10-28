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


struct node {
    char value[256];
    char key[256];
    struct node* next;
};

typedef struct node node_t;

node_t *create_new_node(char *key, char *value);
int find_node(node_t *head, char *key);
void printlist(node_t *head);
node_t *insert_at_head(node_t **head, node_t *node_to_insert);
void delete_node(node_t **head, char *keys);
int update_node(node_t *head, char *key, char *newvalue);

#endif /* j_node_h */
