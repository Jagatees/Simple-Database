#include "database.h"


const int MAX_INSTRUCTION = 11;
const char *INVAILD_INSTRUCTION = "Unknown command. Please type 'HELP' for the list of commands.\n";
const char *DB_INSTRUCTION[MAX_INSTRUCTION] = {
    "SHOW", "ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "OPEN", "SAVE", "EXIT", "HELP", "BACK",
};

typedef enum {
    SHOW, ALL, INSERT, QUERY, UPDATE, DELETE, OPEN, SAVE, EXIT, HELP, BACK, UNKNOWN_COMMAND
} InstructionEnum;

typedef enum {
    DB_CLOSE,
    DB_OPEN
} DBState;

DBState db_State = DB_CLOSE;

void switchState(const char* user_input) {
    if (strcmp(user_input, DB_INSTRUCTION[OPEN]) == 0) {
        db_State = DB_OPEN;
    } else if (strcmp(user_input, DB_INSTRUCTION[EXIT]) == 0) {
        db_State = DB_CLOSE;
    }
    
}


InstructionEnum getInstruction(const char *user_input){
    for (int i = 0; i < MAX_INSTRUCTION; i++) {
            if (strcmp(user_input, DB_INSTRUCTION[i]) == 0) {
                return (InstructionEnum)i;
            }
        }
        return UNKNOWN_COMMAND;
}


void openInstruction(char *user_input[], KeyValueNode **head) {

    if (readFromFile(getWorkingDirectory(user_input[1]), head))
    {
        printf("Save Key & Values into cahe from %s\n", user_input[1]);
        switchState(user_input[0]);
    }
    else
    {
        printf("Unable to find %s at location\n", user_input[1]);
    }
}


void showAllInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter >= 2 && strcmp(user_input[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(user_input[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", lenNode(*head));
        printNode(*head);
    }
}



void exitInstruction(char *user_input[]) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[EXIT]) == 0) // DELETE INSTRUCTION
    {
        switchState(user_input[0]);
        printf("Exit EzDB.EXE\n");
    }
}


void helpInstruction(DBState db_state) {
    
    if (db_State == DB_CLOSE) {
    
        printf("--------------HELP PAGE--------------\n");
        printf("Current State : Database Close\n");
        printf("OPEN [filename.txt] : Load data from the specified file into the cache.\n");
        printf("Please place your 'XXX.txt' file at the following location: %s\n",printWorkingDirectory());
        printf("EXIT :  EXIT the EzDB.EXE\n");

        
    } else if (db_State == DB_OPEN){
        
        printf("--------------HELP PAGE--------------\n");
        printf("Current State : Database OPEN\n");
        printf("SHOW ALL: Display all entries in the table.\n");
        printf("INSERT [Key] [Value]: Add a new entry to the table.\n");
        printf("QUERY [Key]: Retrieve the value associated with the specified key.\n");
        printf("UPDATE [Key] [Value]: Modify the value associated with the given key.\n");
        printf("DELETE [Key]: Remove the entry associated with the specified key from the table.\n");
        printf("SAVE [filename.txt]: Save the current table data to a text file.\n");
        printf("BACK: Transitioning from 'db open' state to 'db close' state.\n");
        printf("Exit: Terminate the EzDB.EXE.\n");

    }
    
}


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


char* getWorkingDirectory(char* user_input){
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        strcat(cwd, "/");
        return strcat(cwd, user_input);
    }
    else
    {
        return "getcwd() error";
    }
    
    
}

char* printWorkingDirectory(){
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        return strcat(cwd, "/");
    }
    else
    {
        return "Unable to get working directory";
    }
    
    
}


void saveInstruction(char *user_input[], KeyValueNode **head) {
    
    if (strcmp(user_input[0], DB_INSTRUCTION[SAVE]) == 0)
    {
        saveFromFile(getWorkingDirectory(user_input[1]), head);
        printf("SAVE Data to this file %s\n", user_input[1]);
    }
    
}


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
                case BACK:
                    db_State = DB_CLOSE;
                    break;
                default:
                    printf(INVAILD_INSTRUCTION);
                    break;
            }
            break;
        }
        
    return 0;
    
}

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

    char line[1024][1024];
    int countPage = 0;
    
    // Read lines from the file into the lines array
    while (fgets(line[countPage], sizeof(line[0]), file))
    {
        countPage++;
    }
    
    fclose(file);
    
    for (int i = countPage - 1; i >= 0; i--)
    {
        // change this based on u want " " Space or "\t" for tab space in between
        char *key = strtok(line[i], " ");
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

    
    return 1;
}


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
