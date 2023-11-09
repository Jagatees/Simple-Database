#include "database.h"

const int MAX_INSTRUCTION = 10;
const char *FILE_NOT_FOUND = "Unable to find %s at location\n";
const char *DB_INSTRUCTION[MAX_INSTRUCTION] = {
    "SHOW", "ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "OPEN", "SAVE", "EXIT", "HELP",
};

typedef enum {
    SHOW, ALL, INSERT, QUERY, UPDATE, DELETE, OPEN, SAVE, EXIT, HELP, UNKNOWN_COMMAND
} CommandType;

typedef enum {
    db_Close,
    db_Open
} DBState;

DBState db_state = db_Close;


/**
 * @brief Allow user to switch between the two different state which is db_open or db_close
 *
 * @param user_input String containing user input
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
 * @brief Use user input to return the instruction type the user is trying to excuted
 *
 * @param user_input A string containing the user's input
 * @return CommandType An enum value representing the recognized command type.
 */
CommandType getCommandType(const char *user_input){
    for (int i = 0; i < MAX_INSTRUCTION; i++) {
            if (strcmp(user_input, DB_INSTRUCTION[i]) == 0) {
                return (CommandType)i;
            }
        }
        return UNKNOWN_COMMAND;
}

/**
 * @brief Handles the 'OPEN' command, it also find the current dir and append it to what teh user enter for the file name.
 *
 * @param inv A string containing the user's input
 * @param head A pointer to the head node of the linked list representing the database.
 * @return void
 */
void handleOpenCommand(char *inv[], node_t **head) {
    
    char cwd[1024];
    
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


void handleShowAllCommand(char *inv[], int inc, node_t **head) {
    
    if (inc >= 2 && strcmp(inv[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(inv[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", list_node(*head));
        printlist(*head);
    }
}



void handleExitCommand(char *inv[]) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[EXIT]) == 0) // DELETE INSTRUCTION
    {
        switch_state(inv[0]);
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


void handleInsertCommand(char *inv[], node_t **head) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[INSERT]) == 0) {
        int isfound = find_node(*head, inv[1]);
   
        if (isfound == 1)
        {
            printf("The record with Key=%s already exists in the database\n", inv[1]);
        }
        else if (isfound == 0)
        {
            node_t *tmp = create_new_node(inv[1], inv[2]);
            insert_at_head(head, tmp);
            printf("A new record of Key=%s Value=%s is successfully inserted\n", inv[1], inv[2]);
        }
   
    }
    
}


void handleQueryCommand(char *inv[], node_t **head) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[QUERY]) == 0)
    {
        char *isfound = find_node_return_string(*head, inv[1]);
   
        if (strcmp(isfound, "EMPTY") != 0)
        {
            printf("A record of Key=%s, Value= %s is found in the database.\n", inv[1], isfound);
        }
        else if (strcmp(isfound, "EMPTY") == 0)
        {
            printf("There is no record with Key=%s found in the database\n", inv[1]);
        }
   
    }
    
}


void handleUpdateCommand(char *inv[], node_t **head) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[UPDATE]) == 0)
    {
   
        int isfound = find_node(*head, inv[1]);
   
        if (isfound == 1)
        {
            update_node(*head, inv[1], inv[2]);
            printf("The value for the record of Key=%s is successfully updated.\n", inv[1]);
        }
        else if (isfound == 0)
        {
            printf("There is no record with Key=%s found in the database.\n", inv[1]);
        }
   
    }
    
}


void handleDeleteCommand(char *inv[], node_t **head) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[DELETE]) == 0)
    {
        printf("The record of Key=%s is successfully deleted.\n", inv[1]);
        delete_node(head, inv[1]);
    }
    
}

/**
 * @brief Handles the 'SAVE' command, which writes the current state of the database to a file.
 *
 * @param inv An array of strings representing user input split into arguments.
 * @param head A pointer to the head node of the linked list representing the database.
 * @return void
 */
void handleSaveCommand(char *inv[], node_t **head) {
    
    if (strcmp(inv[0], DB_INSTRUCTION[SAVE]) == 0)
    {
        printf("SAVE Data to this file %s\n", inv[1]);
        
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            strcat(cwd, "/");
            strcat(cwd, inv[1]);
        }
        else
        {
            perror("getcwd() error");
            // Handle error here
        }
        
        saveFromFile(cwd, head);
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
                handleOpenCommand(inv, head);
            } else if (cmdType == HELP) {
                handleHelpCommand(db_state);
            } else if (cmdType == EXIT) {
                handleExitCommand(inv);
                return 1;
            } else {
                printf("Please Load in a .txt file first before entering into database\n");
            }
            break;
        case db_Open:
            switch (cmdType) {
                case SHOW:
                    handleShowAllCommand(inv, inc, head);
                    break;
                case EXIT:
                    handleExitCommand(inv);
                    return 1;
                    break;
                case INSERT:
                    handleInsertCommand(inv, head);
                    break;
                case QUERY:
                    handleQueryCommand(inv, head);
                    break;
                case HELP:
                    handleHelpCommand(db_state);
                    break;
                case UPDATE:
                    handleUpdateCommand(inv, head);
                    break;
                case DELETE:
                    handleDeleteCommand(inv, head);
                    break;
                case SAVE:
                    handleSaveCommand(inv, head);
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
