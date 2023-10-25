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


void printlist(node_t *head) {
    node_t *temporary = head;
    
    while (temporary != NULL) {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    
    printf("\n");
}



int main(int argc, const char * argv[]) {
    
    node_t n1,n2,n3;
    node_t *head;
    
    n1.value = 1;
    n2.value = 2;
    n3.value = 3;
    
    head = &n2;
    
    n1.next = &n3;
    n2.next = &n1;
    n3.next = NULL;
    
  
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


