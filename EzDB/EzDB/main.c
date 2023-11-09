
// Include C Header Files
#include <stdio.h>  // input-output
#include <ctype.h>  // Character Type
#include <string.h> // String Manipulation
#include <stdlib.h> // Standard Library

// Include Custom Header Files
#include "utility.h"  // Store General Variable
#include "database.h" // Structure of Database
#include "j_node.h"   // Structure of Linked List

int main(int argc, const char *argv[])
{
    
    // init linked head to null on start
    node_t *head = NULL;

    // Store user input
    char user_input[MAX_USER_INPUT];

    // Database Loop (think of it like a game loop) , 0 == still in database , 1 == will exit database
    int inDatabase = 0;

    // Split User Input
    int counter = 0;
    char *split_user_input[MAX_USER_INPUT];

    // Print Welcome Message
    printf("-------ICT 1002-------\n");
   

    do
    {
        // Print Input Line
        printf("Enter INSTRUCTION :");

        // store user input
        fgets(user_input, MAX_USER_INPUT, stdin);

        // init counter to zero
        counter = 0;
        // store user input in a split format
        split_user_input[counter] = strtok(user_input, characters);

        // Split String - until reach null mean end of user input
        while (split_user_input[counter] != NULL)
        {
            counter++;
            split_user_input[counter] = strtok(NULL, characters);
        }

        // init database logic
        inDatabase = databaseLogic(split_user_input, counter, &head);

    } while (!inDatabase);

    return 0;
}
