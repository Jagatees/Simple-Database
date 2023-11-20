#include "database.h"


// MAX Number of Instruction
const int MAX_INSTRUCTION = 10;
const char *INVAILD_INSTRUCTION = "Unknown command. Please type 'HELP' for the list of commands.\n";
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
    DB_CLOSE,
    DB_OPEN
} DBState;

// Initalize DB State to Close on Start
DBState db_State = DB_CLOSE;


/**
 * @brief Used to switch between the two different states for this database which are db_Open & db_Close
 *
 * @param user_input String that holds the user input
 * @return Void
 */
void switchState(const char* user_input) {
    if (strcmp(user_input, DB_INSTRUCTION[OPEN]) == 0) {
        db_State = DB_OPEN;
    } else if (strcmp(user_input, DB_INSTRUCTION[EXIT]) == 0) {
        db_State = DB_CLOSE;
    }
    
}


/**
 * @brief Use user_input to search throught the DB instruction list
 *
 * @param user_input String that holds the user input
 * @return InstructionEnum
 */
InstructionEnum getInstruction(const char *user_input){
    for (int i = 0; i < MAX_INSTRUCTION; i++) {
            if (strcmp(user_input, DB_INSTRUCTION[i]) == 0) {
                return (InstructionEnum)i;
            }
        }
        return UNKNOWN_COMMAND;
}

/**
 * @brief Handle the Open Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void openInstruction(char *user_input[], KeyValueNode **head) {
    
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
        switchState(user_input[0]);
    }
    else
    {
        printf("Unable to find %s at location\n", user_input[1]);
    }
}

/**
 * @brief Handle the Show All Instruction
 *
 * @param user_input String that holds the user input
 * @param counter length of user_input
 * @param head  node pointing to the head
 * @return void
 */
void showAllInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter >= 2 && strcmp(user_input[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(user_input[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", lenNode(*head));
        printNode(*head);
    }
}


/**
 * @brief Handle the Exit Instruction
 *
 * @param user_input String that holds the user input
 * @return void
 */
void exitInstruction(char *user_input[]) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[EXIT]) == 0) // DELETE INSTRUCTION
    {
        switchState(user_input[0]);
        printf("Exit Database\n");
    }
}

/**
 * @brief Handle the HELP Instruction
 *
 * @param DBState either db_open or db_close
 * @return void
 */
void helpInstruction(DBState db_state) {
    
    if (db_State == DB_CLOSE) {
        
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
        printf("EXIT :  EXIT the program\n");

        
    } else if (db_State == DB_OPEN){
        
        printf("--------------INSTRUCTION LIST--------------\n");
        printf("SHOW ALL: Display all entries in the table.\n");
        printf("INSERT [Key] [Value]: Add a new entry to the table.\n");
        printf("QUERY [Key]: Retrieve the value associated with the specified key.\n");
        printf("UPDATE [Key] [Value]: Modify the value associated with the given key.\n");
        printf("DELETE [Key]: Remove the entry associated with the specified key from the table.\n");
        printf("SAVE [filename.txt]: Save the current table data to a text file.\n");
        printf("Exit: Terminate the program.\n");

    }
    
}

/**
 * @brief Handle the Insert Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void insertInstruction(char *user_input[], KeyValueNode **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[INSERT]) == 0) {
        int isfound = findNode(*head, user_input[1]);
   
        if (isfound == 1)
        {
            printf("The record with Key=%s already exists in the database\n", user_input[1]);
        }
        else if (isfound == 0)
        {
            KeyValueNode *tmp = createNode(user_input[1], user_input[2]);
            insertHead(head, tmp);
            printf("A new record of Key=%s Value=%s is successfully inserted\n", user_input[1], user_input[2]);
        }
   
    }
    
}

/**
 * @brief Handle the Query Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void queryInstruction(char *user_input[], KeyValueNode **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[QUERY]) == 0)
    {
        char *isfound = findNodereturnString(*head, user_input[1]);
   
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

/**
 * @brief Handle the Update Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void updateInstruction(char *user_input[], KeyValueNode **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[UPDATE]) == 0)
    {
   
        int isfound = findNode(*head, user_input[1]);
   
        if (isfound == 1)
        {
            updateNode(*head, user_input[1], user_input[2]);
            printf("The value for the record of Key=%s is successfully updated.\n", user_input[1]);
        }
        else if (isfound == 0)
        {
            printf("There is no record with Key=%s found in the database.\n", user_input[1]);
        }
   
    }
    
}

/**
 * @brief Handle the Delete Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void deleteInstruction(char *user_input[], KeyValueNode **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[DELETE]) == 0)
    {
        
        int isfound = findNode(*head, user_input[1]);
        
        if (isfound == 1)
        {
            printf("The record of Key=%s is successfully deleted.\n", user_input[1]);
            deleteNode(head, user_input[1]);
        }
        else if (isfound == 0)
        {
            printf("There is no record with Key=%s found in the database.\n", user_input[1]);
        }
        
        
       
    }
    
}

/**
 * @brief Handle the Save Instruction
 *
 * @param user_input String that holds the user input
 * @param head  node pointing to the head
 * @return void
 */
void saveInstruction(char *user_input[], KeyValueNode **head) {
    
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


/**
 * @brief Switch Case in between db_states and db_instruciton
 *
 * @param user_input String that holds the user input
 * @param counter length of user_input
 * @param head  node pointing to the head
 * @return void
 */
int databaseLogic(char *user_input[], int counter, KeyValueNode **head)
{
    InstructionEnum instructionType;

    if (user_input[0] == NULL) {
        printf("Empty Input\n");
        return 0;
    } else {
        instructionType = getInstruction(user_input[0]);
    }

    switch (db_State) {
        case DB_CLOSE:
            if (instructionType == OPEN) {
                openInstruction(user_input, head);
            } else if (instructionType == HELP) {
                helpInstruction(db_State);
            } else if (instructionType == EXIT) {
                exitInstruction(user_input);
                return 1;
            } else {
                printf(INVAILD_INSTRUCTION);
            }
            break;
        case DB_OPEN:
            switch (instructionType) {
                case SHOW:
                    showAllInstruction(user_input, counter, head);
                    break;
                case EXIT:
                    exitInstruction(user_input);
                    return 1;
                    break;
                case INSERT:
                    insertInstruction(user_input, head);
                    break;
                case QUERY:
                    queryInstruction(user_input, head);
                    break;
                case HELP:
                    helpInstruction(db_State);
                    break;
                case UPDATE:
                    updateInstruction(user_input, head);
                    break;
                case DELETE:
                    deleteInstruction(user_input, head);
                    break;
                case SAVE:
                    saveInstruction(user_input, head);
                    break;
                default:
                    printf(INVAILD_INSTRUCTION);
                    break;
            }
            break;
        }
        
    return 0;
    
}

/**
 * @brief Remove the space in the data
 *
 * @param user_input String that holds the user input
 * @return char*
 */
char *rtrim(char *user_input)
{
    int lenght = (unsigned)strlen(user_input);

    int index = lenght - 1;
    while (index >= 0 && isspace(user_input[index]))
    {
        index--;
    }
    user_input[index + 1] = '\0';
    return user_input;
}

/**
 * @brief Read Text File with .txt after name Ex, XXX.txt
 *
 * @param mainHead  node pointing to the head
 * @param filename Take in File Name
 * @return int 1 or 0 whether it successed or not
 */
int readFromFile(const char *filename, KeyValueNode **mainHead)
{

    FILE *file = fopen(filename, "r");

    KeyValueNode *head;
    KeyValueNode *tmp;

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
            int x = findNode(head, key);
            if (x == 0)
            {
                tmp = createNode(rtrim(key), rtrim(value));
                head = insertHead(&head, tmp);
                *mainHead = head;
            }
        }
    }

    fclose(file);
    
    return 1;
    

    
}

/**
 * @brief Save Text File into XXX.txt
 *
 * @param filename Take in File Name
 * @param head  node pointing to the head
 * @return int 1 or 0 whether it successed or not
 */
void saveFromFile(const char *filename, KeyValueNode **head)
{

    KeyValueNode *temporary = *head;

    FILE *file = fopen(filename, "w");

    fprintf(file, "%s\t%s\n", "Key", "Value");

    while (temporary != NULL)
    {
        fprintf(file, "%s %s\n", temporary->key, temporary->value);
        temporary = temporary->next;
    }

    fclose(file);
}
