//
//  j_node.c
//  EzDB
//
//  Created by Jagateesvaran on 28/10/23.
//

#include "j_node.h"

// CREATE A NODE
node_t *create_new_node(char *key, char *value) {
    node_t *result = malloc(sizeof(node_t));
    strcpy(result->value, value);
    strcpy(result->key, key);
    return result;
}


// INSERT NEW NODE INTO NODE LIST
node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}


// Show All - (Print)
void printlist(node_t *head) {
    node_t *temporary = head;
    
    printf("Keys :  Value \n");

    while (temporary != NULL) {
        printf("%s :  %s \n", temporary->key, temporary->value);
        temporary = temporary->next;
    }
}

// Search Query
int find_node(node_t *head, char *key) {
    node_t *tmp = head;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0) {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

// delete node
void delete_node(node_t **head, char *keys) {
    node_t *previous = *head;
    node_t *current = *head;
    
    // Check if the head node is the one to be deleted
    if(strcmp(current->key, keys) == 0){
        *head = current->next;
        free(current);
        return;
    }
        
    // Search for the node to be deleted
    while(current != NULL && strcmp(current->key, keys) != 0) {
        previous = current;
        current = current->next;
    }

    // If the key wasn't found in the list
    if(current == NULL) {
        printf("Key not found in the list\n");
        return;
    }

    // Delete the node
    previous->next = current->next;
    free(current);
}

// UPDATE
int update_node(node_t *head, char *key, char *newvalue) {
    node_t *tmp = head;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0) {
            printf("Updated key \"%s\" with new value \n", tmp->value);
            strcpy(tmp->value, newvalue);
            printf("Updated key \"%s\" with new value \n", tmp->value);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
