//
//  main.c
//  EzDB
//
//  Created by Jagateesvaran on 24/10/23.
//

// C Libary
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "database.h"


struct node {
    int value;
    struct node* next;
};

typedef struct node node_t;

//SHOW ALL: to show all the current records. (Done)
//• INSERT: to add a new record to the database. (Done)
//• QUERY: to search for a record in the database. (Done)
//• UPDATE: to update the value for a given record. (PENDIND) (2 arg the query function)
//• DELETE: to delete a record from the database. (Done)


// Show All - (Print)
void printlist(node_t *head) {
    node_t *temporary = head;
    
    while (temporary != NULL) {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    
    printf("\n");
}


// Create A New Node
node_t *create_new_node(int value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

// Insert
node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

// Search Query
node_t *find_node(node_t *head, int value) {
    node_t *tmp = head;
    while (tmp != NULL) {
        if (tmp->value == value) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

// delete node
void delete_node(node_t **head, int index) {
    node_t *previous = *head;
    node_t *current = *head;
    
    if (*head == NULL){
        printf("list is already empty");
    }
    else if(index == 1){
        *head = current->next;
        free(current);
        current = NULL;
    }
    else {
        while (index !=  1) {
            previous = current;
            current = current->next;
            index--;
        }
        previous->next = current->next;
        free(current);
        current = NULL;
    }
}



int main(int argc, const char * argv[]) {
    
    node_t *head = NULL;
    node_t *tmp;
    
    for (int i = 0; i < 15; i++) {
        tmp = create_new_node(i);
        head = insert_at_head(&head, tmp);
    }
    
    
    tmp = find_node(head, 13);
    printf("Found Number : %d\n", tmp->value);
    
    printlist(head);
    
    // Index Zero , give error
    delete_node(&head, 1);

    printlist(head);

    
    
    
    
//    // Get user input , 
//    // max number of string a user can enter in the line
//    char user_input[MAX_USER_INPUT];
//    int inDatabase = 0;
//    // rename this variable
//    int inc = 0;
//    char *inv[MAX_USER_INPUT];
//    
//    
//    printf("Welcome to EzDB\n");
//    
//    do {
//        // Display Text Message
//        printf("Enter Query :");
//        // Get a string os user input
//        fgets(user_input, MAX_USER_INPUT, stdin);
//        
//        
//        // conver to upper case
//        for (int i = 0; user_input[i]; i++) {
//            user_input[i] = toupper((unsigned char)user_input[i]);
//        }
//        
//        printf("Uppercase: %s", user_input);
//
//        
//        // still not sure it like remove stuff from the string and store in inv[0] ?
//        inc = 0;
//        inv[inc] = strtok(user_input, characters);
//
//        // Split String
//        // Place a NULL as a last value
//        // break from there
//        while (inv[inc] != NULL) {
//            inc++;
//            inv[inc] = strtok(NULL, characters);
//        }
//        
//        // retturn (1 == break loop , 0 = keep looping)
//        inDatabase = logic_databse(inv, inc);
//        
//    } while (!inDatabase);
//   
    return 0;
}


