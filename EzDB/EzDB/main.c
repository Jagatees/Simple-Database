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


void printFileContents(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file for reading
    
    // Check if the file was opened successfully
    if (!file) {
        perror("Error opening file");  // Print a descriptive error message
        return;
    }

    char line[1024];  // Buffer to store each line from the file
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Print each line
    }

    fclose(file);  // Close the file
}

int main(int argc, const char *argv[])
{   
    
    // cahnge so can just read from my own dir in future
    const char *filename = "/Users/jagatees/Desktop/Files/Github_Hubs/Console_ChatBot/C_Console_Chat_Bot/EzDB/EzDB/table.txt";
    printFileContents(filename);
    
    

    //    node_t *head = NULL;
    //    node_t *tmp;
    //
    //    tmp = create_new_node("MANGO", "6.5");
    //    head = insert_at_head(&head, tmp);
    //
    //    tmp = create_new_node("ORANGE", "3.3");
    //    head = insert_at_head(&head, tmp);
    //
    //    tmp = create_new_node("APPLE", "4.2");
    //    head = insert_at_head(&head, tmp);
    //
    //
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
    //        inDatabase = logic_databse(inv, inc, &head);
    //
    //    } while (!inDatabase);

    return 0;
}
