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
#include "j_node.h"



int main(int argc, const char * argv[]) {
   
    
    
    // Load some Fake Data into node
    node_t *head = NULL;
    node_t *tmp;
    
    tmp = create_new_node("MANGO", "6.5");
    head = insert_at_head(&head, tmp);

    tmp = create_new_node("ORANGE", "3.3");
    head = insert_at_head(&head, tmp);

    tmp = create_new_node("APPLE", "4.2");
    head = insert_at_head(&head, tmp);
    
    
    // Get user input ,
    // max number of string a user can enter in the line
    char user_input[MAX_USER_INPUT];
    int inDatabase = 0;
    // rename this variable
    int inc = 0;
    char *inv[MAX_USER_INPUT];
    
    
    printf("Welcome to EzDB\n");
    
    do {
        // Display Text Message
        printf("Enter Query :");
        // Get a string os user input
        fgets(user_input, MAX_USER_INPUT, stdin);
        
        
        // conver to upper case
        for (int i = 0; user_input[i]; i++) {
            user_input[i] = toupper((unsigned char)user_input[i]);
        }
        
        
        // still not sure it like remove stuff from the string and store in inv[0] ?
        inc = 0;
        inv[inc] = strtok(user_input, characters);

        // Split String
        // Place a NULL as a last value
        // break from there
        while (inv[inc] != NULL) {
            inc++;
            inv[inc] = strtok(NULL, characters);
        }
        
        // retturn (1 == break loop , 0 = keep looping)
        inDatabase = logic_databse(inv, inc, &head);
        
    } while (!inDatabase);
    
    
    
    
    
    
//    tmp = find_node(head, 13);
//    printf("Found Number : %d\n", tmp->value);
//    
//    printlist(head);
//    
//    // Index Zero , give error
//    delete_node(&head, 1);
//
//    printlist(head);
//
//    update_node(head, 4, 400);
//    printlist(head);

    
    
    return 0;
}


