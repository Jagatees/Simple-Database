//
//  main.c
//  EzDB
//
//  Created by Jagateesvaran on 24/10/23.
//

// C Libary
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// My Lib
#include "database.h"

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */


#define MAX_USER_INPUT 256
const char *characters = " ?\t\n";


// Get user input
// check is it is empty first
// check what is the intent
// send to the write function to handle the write intent
// if not then return false say wrong entry
// user enter exit can exit the databse
// 1 = keep looping , 0 stop looping

int main(int argc, const char * argv[]) {
    
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
        
        printf("Uppercase: %s", user_input);

        
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
        
        inDatabase =  init_databse(inv, inc);
        // 1 == break loop , 0 = keep looping
    } while (!inDatabase);
   
        
    
    return 0;
}
