
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
    // Print SIT Declaration
    SIT_DECLARATION();
   
    // Init Head node to NULL on Start
    node_t *head = NULL;
    
    // Database Loop, 0 == still in database , 1 == will exit database
    int inDatabase = 0;

    // User Input & Split User Input & Counter is Length of User input
    char user_input[MAX_USER_INPUT];
    int counter = 0;
    char *split_user_input[MAX_USER_INPUT];

    // Database Loop
    do
    {
        // Print Input Line
        printf("ENTER COMMAND :");

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
