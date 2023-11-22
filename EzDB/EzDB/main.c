
// Include C Header Files
#include <stdio.h>  // input-output
#include <ctype.h>  // Character Type
#include <string.h> // String Manipulation
#include <stdlib.h> // Standard Library

// Include Custom Header Files
#include "utility.h"  // Store General Variable
#include "database.h" // Structure of Database
#include "databaseNode.h"  // Structure of Linked List

int main(int argc, const char *argv[])
{
    PRINT_SIT_DECLARATION();
   
    KeyValueNode *head = NULL;
    
    // Database Loop, 0 == still in database , 1 == will exit database
    int inDatabase = 0;

    // User Input & Split User Input & Counter is Length of User input
    char user_input[MAX_USER_INPUT];
    int counter = 0;
    char *split_user_input[MAX_USER_INPUT];

    // Database Loop
    do
    {
        printf("ENTER COMMAND :");

        fgets(user_input, MAX_USER_INPUT, stdin);

        counter = 0;
        split_user_input[counter] = strtok(user_input, characters);

        while (split_user_input[counter] != NULL)
        {
            counter++;
            split_user_input[counter] = strtok(NULL, characters);
        }

        inDatabase = databaseLogic(split_user_input, counter - 1, &head);

    } while (!inDatabase);

    return 0;
}
