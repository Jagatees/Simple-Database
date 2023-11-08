//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"



const int MAX_INSTRUCTION = 10;
const char *FILE_EXTENSION = ".txt";
const char *FILE_NOT_FOUND = "Unable to find %s at location\n";
const char *DB_INSTRUCTION[MAX_INSTRUCTION] = {
    "SHOW", "ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "OPEN", "SAVE", "EXIT", "HELP",
};

typedef enum {
    SHOW, ALL, INSERT, QUERY, UPDATE, DELETE, OPEN, SAVE, EXIT, HELP, UNKNOWN_COMMAND
} CommandType;

CommandType getCommandType(const char *user_input){
    for (int i = 0; i < MAX_INSTRUCTION; i++) {
            if (strcmp(user_input, DB_INSTRUCTION[i]) == 0) {
                return (CommandType)i;
            }
        }
        return UNKNOWN_COMMAND;
}



typedef enum {
    db_Close,
    db_Open
} DBState;

DBState db_state = db_Close;


// Handle Database instruction based on user input

/*
 When get user inpput
 
 If input is blank
    Is Open == true
        instruction
    Is Open == False
        can not do instruction
 
 Is input is Exit
 Is input is Exit

 */

// Implement this to make nice
// state machine
// switch case
// inspried by elson ntu, GOD, touch by his pressence
// comment chuck
// cacll the function with different args

void switch_state(const char* user_input) {
    if (strcmp(user_input, DB_INSTRUCTION[OPEN]) == 0)
    {
        db_state = db_Open;

    } else if (strcmp(user_input, DB_INSTRUCTION[EXIT]) == 0) {
        db_state = db_Close;
    }
    
}

void handleOpenCommand(const char **inv, node_t **head) {
    
    char cwd[MAX_PATH_LEN];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        strcat(cwd, "/");
        strcat(cwd, inv[1]);
    }
    else
    {
        perror("getcwd() error");
    }

    if (strcmp(inv[1], "Color.txt") == 0 && readFromFile(cwd, head))
    {
        printf("Save Key & Values into cahe from %s\n", inv[1]);
        switch_state(inv[0]);
    }
    else
    {
        printf("Unable to find %s at location\n", inv[1]);
    }
}

void handleShowAllCommand(const char **inv, int inc, node_t **head) {
    
    if (inc >= 2 && strcmp(inv[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(inv[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", list_node(*head));
        printlist(*head);
    }
}

void handleExitCommand(const char **inv) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[EXIT]) == 0) // DELETE INSTRUCTION
    {
        switch_state(inv[0]);
        printf("Exit Database\n");
    }
}

void handleHelpCommand(DBState db_state) {
    
    if (db_state == db_Close) {
        
        char cwd[MAX_PATH_LEN];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            strcat(cwd, "/");
        }
        else
        {
            perror("getcwd() error");
        }
        
        printf("--------------INSTRUCTION LIST--------------\n");
        printf("OPEN [filename.txt] : Load data from the specified file into the cache.\n");
        printf("Please place your 'Color.txt' file at the following location: %s\n",cwd);
        printf("Exit :  Exit the EXE\n");

        
    } else if (db_state == db_Open){
        
        printf("--------------INSTRUCTION LIST--------------\nSHOW ALL \t\t\t : PRINT OUT TABLE\nINSERT [Key] [Value] : Insert Into Table\nQUERY [Key] \t\t : Display Data from table\nUPDATE [Key] [Value] : Update a value in the table\nDELETE [Key] \t\t : remove key from table\nSAVE [filename.txt]  : save data from cache into .txt\nExit :  Exit the ExBD\n");
    }
    
}


int databaseLogic(char *inv[], int inc, node_t **head)
{
    CommandType cmdType;

    if (inv[0] == NULL) {
        printf("Empty Input\n");
        return 0;
    } else {
        cmdType = getCommandType(inv[0]);
    }

    switch (db_state) {
        case db_Close:
            if (cmdType == OPEN) {
                handleOpenCommand((const char **)inv, head);
            } else if (cmdType == HELP) {
                handleHelpCommand(db_state);
            } else if (cmdType == EXIT) {
                handleExitCommand((const char **)inv);
                return 1;
            } else {
                printf("Please Load in a .txt file first before entering into database\n");
            }
            break;
        case db_Open:
            switch (cmdType) {
                case SHOW:
                    handleShowAllCommand((const char **)inv, inc, head);
                    break;
                case EXIT:
                    handleExitCommand((const char **)inv);
                    return 1;
                    break;
                case HELP:
                    handleHelpCommand(db_state);
                    break;
                default:
                    printf("Unknown command. Please type 'HELP' for the list of commands.\n");
                    break;
            }
            break;
        }
        
    return 0;
    
    
///////////
    
//    if (inv[0] == NULL)
//    {
//        printf("Empty Input\n");
//        return 0;
//    }
//    else if (strcmp(inv[0], db_instruction.EXIT) == 0) // DELETE INSTRUCTION
//    {
//        switch_state(db_instruction.EXIT);
//        printf("Exit Database\n");
//        return 1;
//    }
//    
    
    
    
//    switch (db_state) {
//        case db_Close:
//            if (strcmp(inv[0], db_instruction.OPEN) == 0) // DELETE INSTRUCTION
//            {
//                char cwd[MAX_PATH_LEN];
//                if (getcwd(cwd, sizeof(cwd)) != NULL)
//                {
//                    strcat(cwd, "/");
//                    strcat(cwd, inv[1]);
//                }
//                else
//                {
//                    perror("getcwd() error");
//                }
//
//                if (strcmp(inv[1], "Color.txt") == 0 && readFromFile(cwd, head))
//                {
//                    printf("Save Key & Values into cahe from %s\n", inv[1]);
//                    switch_state(inv[0]);
//                }
//                else
//                {
//                    printf("Unable to find %s at location\n", inv[1]);
//                }
//                return 0;
//            }
//            // Check User Input Match Instruction HELP
//            else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
//            {
//                
//                char cwd[MAX_PATH_LEN];
//                if (getcwd(cwd, sizeof(cwd)) != NULL)
//                {
//                    strcat(cwd, "/");
//                }
//                else
//                {
//                    perror("getcwd() error");
//                }
//
//                printf("--------------INSTRUCTION LIST--------------\n");
//                printf("OPEN [filename.txt] : Load data from the specified file into the cache.\n");
//                printf("Please place your 'Color.txt' file at the following location: %s\n",cwd);
//                printf("Exit :  Exit the EXE\n");
//
//                return 0;
//            }
//            else
//            {
//                printf("Please Load in a .txt file first before entering into database\n");
//                return 0;
//            }
//            break;
//        case db_Open:
//            // Check User Input Match Instruction SHOW ALL
//            if (inc >= 2 && strcmp(inv[0], db_instruction.SHOW) == 0 && strcmp(inv[1], db_instruction.ALL) == 0)
//            {
//                printf("There are in total %i records found: \n", list_node(*head));
//                printlist(*head);
//                return 0;
//            }
//            // Check User Input Match Instruction INSERT
//            else if (strcmp(inv[0], db_instruction.INSERT) == 0)
//            {
//                int isfound = find_node(*head, inv[1]);
//
//                if (isfound == 1)
//                {
//                    printf("The record with Key=%s already exists in the database\n", inv[1]);
//                }
//                else if (isfound == 0)
//                {
//                    node_t *tmp = create_new_node(inv[1], inv[2]);
//                    insert_at_head(head, tmp);
//                    printf("A new record of Key=%s Value=%s is successfully inserted\n", inv[1], inv[2]);
//                }
//
//                return 0;
//            }
//            // Check User Input Match Instruction QUERY
//            else if (strcmp(inv[0], db_instruction.QUERY) == 0)
//            {
//
//                char *isfound = find_node_return_string(*head, inv[1]);
//
//                if (strcmp(isfound, "EMPTY") != 0)
//                {
//                    printf("A record of Key=%s, Value= %s is found in the database.\n", inv[1], isfound);
//                }
//                else if (strcmp(isfound, "EMPTY") == 0)
//                {
//                    printf("There is no record with Key=%s found in the database\n", inv[1]);
//                }
//
//                return 0;
//            }
//            // Check User Input Match Instruction UPDATE
//            else if (strcmp(inv[0], db_instruction.UPDATE) == 0)
//            {
//
//                int isfound = find_node(*head, inv[1]);
//
//                if (isfound == 1)
//                {
//                    update_node(*head, inv[1], inv[2]);
//                    printf("The value for the record of Key=%s is successfully updated.\n", inv[1]);
//                }
//                else if (isfound == 0)
//                {
//                    printf("There is no record with Key=%s found in the database.\n", inv[1]);
//                }
//
//                return 0;
//            }
//            // Check User Input Match Instruction DELETE
//            else if (strcmp(inv[0], db_instruction.DELETE) == 0) // DELETE INSTRUCTION
//            {
//
//                printf("The record of Key=%s is successfully deleted.\n", inv[1]);
//                delete_node(head, inv[1]);
//                return 0;
//            }
//            // Check User Input Match Instruction OPEN
//
//            // Check User Input Match Instruction SAVE
//            else if (strcmp(inv[0], db_instruction.SAVE) == 0) // DELETE INSTRUCTION
//            {
//                printf("SAVE Data to this file %s\n", inv[1]);
//
//                char cwd[MAX_PATH_LEN];
//                if (getcwd(cwd, sizeof(cwd)) != NULL)
//                {
//                    strcat(cwd, "/");
//                    strcat(cwd, inv[1]);
//                }
//                else
//                {
//                    perror("getcwd() error");
//                    // Handle error here
//                }
//
//                saveFromFile(cwd, head);
//                return 0;
//            }
//            // Check User Input Match Instruction HELP
//            else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
//            {
//                printf("--------------INSTRUCTION LIST--------------\nSHOW ALL \t\t\t : PRINT OUT TABLE\nINSERT [Key] [Value] : Insert Into Table\nQUERY [Key] \t\t : Display Data from table\nUPDATE [Key] [Value] : Update a value in the table\nDELETE [Key] \t\t : remove key from table\nSAVE [filename.txt]  : save data from cache into .txt\nExit :  Exit the EXE");
//                return 0;
//            }
//            break;
//    }
    
}

char *rtrim(char *data)
{
    int lenght = (unsigned)strlen(data);

    int index = lenght - 1;
    while (index >= 0 && isspace(data[index]))
    {
        index--;
    }
    data[index + 1] = '\0';
    return data;
}

int readFromFile(const char *filename, node_t **mainHead)
{

    FILE *file = fopen(filename, "r");

    node_t *head;
    node_t *tmp;

    if (*mainHead != NULL)
    {
        head = *mainHead;
    }
    else
    {
        head = NULL;
    }

    if (!file)
    {
        printf("Unable to Open File : Use HELP Instruction\n");
        return 0;
    }

    char line[1024];
    
    while (fgets(line, sizeof(line), file))
    {
        // change this based on u want " " Space or "\t" for tab space in between
        char *key = strtok(line, " ");
        char *value = strtok(NULL, " ");

        if (key && value)
        {
            int x = find_node(head, key);
            if (x == 0)
            {
                tmp = create_new_node(rtrim(key), rtrim(value));
                head = insert_at_head(&head, tmp);
                *mainHead = head;
            }
        }
    }

    fclose(file);
    
    return 1;
    

    
}

void saveFromFile(const char *filename, node_t **head)
{

    node_t *temporary = *head;

    FILE *file = fopen(filename, "w");

    fprintf(file, "%s\t%s\n", "Key", "Value");

    while (temporary != NULL)
    {
        fprintf(file, "%s %s\n", temporary->key, temporary->value);
        temporary = temporary->next;
    }

    fclose(file);
}
