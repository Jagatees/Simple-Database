//
//  main.c
//  EzDB
//
//  Created by Jagateesvaran on 24/10/23.
//


#include <stdio.h>


/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */


#define MAX_USER_INPUT 256


// Get user input
// check is it is empty first
// check what is the intent
// send to the write function to handle the write intent
// if not then return false say wrong entry
// user enter exit can exit the databse
// 1 = keep looping , 0 stop looping

int main(int argc, const char * argv[]) {
    
    
    char user_input[MAX_USER_INPUT];
    int inDatabase = 0;
    
    /* print a welcome message */
    
    printf("Welcome to Hakari Dance Database .\n");

    
    do {
        
        printf("Enter Somthing :");
        // fgets get mutiple string in a 
        fgets(user_input, MAX_USER_INPUT, stdin);
        printf("What user entered %s", user_input);

    
        inDatabase = 1; // 1 == break loop , 0 == keep looping
    } while (!inDatabase);
    
    
    return 0;
}
