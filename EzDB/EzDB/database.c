#include "database.h"


// MAX Number of Instruction
const int MAX_INSTRUCTION = 10;
// message is unable to find file location
const char *FILE_NOT_FOUND = "Unable to find %s at location\n";
// Array of string for instruction
const char *DB_INSTRUCTION[MAX_INSTRUCTION] = {
    "SHOW", "ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "OPEN", "SAVE", "EXIT", "HELP",
};
// List of Enum of Instruction
typedef enum {
    SHOW, ALL, INSERT, QUERY, UPDATE, DELETE, OPEN, SAVE, EXIT, HELP, UNKNOWN_COMMAND
} InstructionEnum;

// Enum of DB State
typedef enum {
    db_Close,
    db_Open
} DBState;

// Initalize DB State to Close on Start
DBState db_state = db_Close;


/**
 * @brief Switch between state db_open and db_close
 * @param user_input Use to
 * @return void
 */
void switch_state(const char* user_input) {
    if (strcmp(user_input, DB_INSTRUCTION[OPEN]) == 0)
    {
        db_state = db_Open;
        
    } else if (strcmp(user_input, DB_INSTRUCTION[EXIT]) == 0) {
        db_state = db_Close;
    }
    
}


/**
 * @brief Switch between state db_open and db_close
 *
 * @param user_input String that holds the user input
 * @return CommandType will return a enum state
 */
InstructionEnum getCommandType(const char *user_input){
    for (int i = 0; i < MAX_INSTRUCTION; i++) {
            if (strcmp(user_input, DB_INSTRUCTION[i]) == 0) {
                return (InstructionEnum)i;
            }
        }
        return UNKNOWN_COMMAND;
}

/**
 * @brief Handle the OPEN Instruction
 * 1 : It will get the current file path of the folder where this code 
 * 2 : It will append what the user type to the path above 
 * 3 : Use that to search for the file
 * 4 : go into the readFromFile(), and return 
 * 5 : Switch the state machine to OPEN 
 *
 * @param user_input String that holds the user input
 * @param head pass in the current head so we can update it if we make any changes to the node
 * @return void
 */
void handleOpenCommand(char *user_input[], node_t **head) {
    
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        strcat(cwd, "/");
        strcat(cwd, user_input[1]);
    }
    else
    {
        perror("getcwd() error");
    }

    if (strcmp(user_input[1], "Color.txt") == 0 && readFromFile(cwd, head))
    {
        printf("Save Key & Values into cahe from %s\n", user_input[1]);
        switch_state(user_input[0]);
    }
    else
    {
        printf("Unable to find %s at location\n", user_input[1]);
    }
}


void handleShowAllCommand(char *user_input[], int counter, node_t **head) {
    
    if (counter >= 2 && strcmp(user_input[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(user_input[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", list_node(*head));
        printlist(*head);
    }
}



void handleExitCommand(char *user_input[]) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[EXIT]) == 0) // DELETE INSTRUCTION
    {
        switch_state(user_input[0]);
        printf("Exit Database\n");
    }
}


void handleHelpCommand(DBState db_state) {
    
    if (db_state == db_Close) {
        
        char cwd[1024];
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


void handleInsertCommand(char *user_input[], node_t **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[INSERT]) == 0) {
        int isfound = find_node(*head, user_input[1]);
   
        if (isfound == 1)
        {
            printf("The record with Key=%s already exists in the database\n", user_input[1]);
        }
        else if (isfound == 0)
        {
            node_t *tmp = create_new_node(user_input[1], user_input[2]);
            insert_at_head(head, tmp);
            printf("A new record of Key=%s Value=%s is successfully inserted\n", user_input[1], user_input[2]);
        }
   
    }
    
}


void handleQueryCommand(char *user_input[], node_t **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[QUERY]) == 0)
    {
        char *isfound = find_node_return_string(*head, user_input[1]);
   
        if (strcmp(isfound, "EMPTY") != 0)
        {
            printf("A record of Key=%s, Value=%s is found in the database.\n", user_input[1], isfound);
        }
        else if (strcmp(isfound, "EMPTY") == 0)
        {
            printf("There is no record with Key=%s found in the database\n", user_input[1]);
        }
   
    }
    
}


void handleUpdateCommand(char *user_input[], node_t **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[UPDATE]) == 0)
    {
   
        int isfound = find_node(*head, user_input[1]);
   
        if (isfound == 1)
        {
            update_node(*head, user_input[1], user_input[2]);
            printf("The value for the record of Key=%s is successfully updated.\n", user_input[1]);
        }
        else if (isfound == 0)
        {
            printf("There is no record with Key=%s found in the database.\n", user_input[1]);
        }
   
    }
    
}


void handleDeleteCommand(char *user_input[], node_t **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[DELETE]) == 0)
    {
        
        int isfound = find_node(*head, user_input[1]);
        
        if (isfound == 1)
        {
            printf("The record of Key=%s is successfully deleted.\n", user_input[1]);
            delete_node(head, user_input[1]);
        }
        else if (isfound == 0)
        {
            printf("There is no record with Key=%s found in the database.\n", user_input[1]);
        }
        
        
       
    }
    
}


void handleSaveCommand(char *user_input[], node_t **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[SAVE]) == 0)
    {
        printf("SAVE Data to this file %s\n", user_input[1]);
        
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            strcat(cwd, "/");
            strcat(cwd, user_input[1]);
        }
        else
        {
            perror("getcwd() error");
            // Handle error here
        }
        
        saveFromFile(cwd, head);
    }
    
}



int databaseLogic(char *user_input[], int counter, node_t **head)
{
    InstructionEnum instructionType;

    if (user_input[0] == NULL) {
        printf("Empty Input\n");
        return 0;
    } else {
        instructionType = getCommandType(user_input[0]);
    }

    switch (db_state) {
        case db_Close:
            if (instructionType == OPEN) {
                handleOpenCommand(user_input, head);
            } else if (instructionType == HELP) {
                handleHelpCommand(db_state);
            } else if (instructionType == EXIT) {
                handleExitCommand(user_input);
                return 1;
            } else {
                printf("Please Load in a .txt file first before entering into database\n");
            }
            break;
        case db_Open:
            switch (instructionType) {
                case SHOW:
                    handleShowAllCommand(user_input, counter, head);
                    break;
                case EXIT:
                    handleExitCommand(user_input);
                    return 1;
                    break;
                case INSERT:
                    handleInsertCommand(user_input, head);
                    break;
                case QUERY:
                    handleQueryCommand(user_input, head);
                    break;
                case HELP:
                    handleHelpCommand(db_state);
                    break;
                case UPDATE:
                    handleUpdateCommand(user_input, head);
                    break;
                case DELETE:
                    handleDeleteCommand(user_input, head);
                    break;
                case SAVE:
                    handleSaveCommand(user_input, head);
                    break;
                default:
                    printf("Unknown command. Please type 'HELP' for the list of commands.\n");
                    break;
            }
            break;
        }
        
    return 0;
    
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
