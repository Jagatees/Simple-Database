#include "database.h"


const int MAX_INSTRUCTION = 11;
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

void PRINT_INVAILD_INSTRUCTION(void) {
    printf("Unknown command. Please type 'HELP' for the list of commands.\n");
}


void openInstruction(char *user_input[], int counter, KeyValueNode **head) {

    if (counter == 1 && readFromFile(getWorkingDirectory(user_input[1]), head, user_input[1]))
    {
        printf("Save Key & Values into cache from %s\n", user_input[1]);
        switchState(user_input[0]);
    }
    else if (counter != 1)
    {
        PRINT_INVAILD_INSTRUCTION();
    }
    
}


void showAllInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter == 1 && strcmp(user_input[0], DB_INSTRUCTION[SHOW]) == 0 && strcmp(user_input[1], DB_INSTRUCTION[ALL]) == 0)
    {
        printf("There are in total %i records found: \n", lenNode(*head));
        printNode(*head);
    }else {
        PRINT_INVAILD_INSTRUCTION();
    }
}



int exitInstruction(char *user_input[], int counter) {
    if (counter == 0 && strcmp(user_input[0], DB_INSTRUCTION[EXIT]) == 0)
    {
        switchState(user_input[0]);
        printf("EXIT EzDB.EXE\n");
        return 1;
    } else {
        PRINT_INVAILD_INSTRUCTION();
        return 0;
    }
}


void helpInstruction(DBState db_state, int counter) {
    
    if (counter == 0) {
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
            printf("EXIT: Terminate the EzDB.EXE.\n");
        }
    }else {
        PRINT_INVAILD_INSTRUCTION();
    }
   
    
}


void insertInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter == 2 && strcmp(user_input[0], DB_INSTRUCTION[INSERT]) == 0) {
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
    }else  {
        PRINT_INVAILD_INSTRUCTION();
    }
    
}


void queryInstruction(char *user_input[], int counter,KeyValueNode **head) {
    
    if (counter == 1 &&strcmp(user_input[0], DB_INSTRUCTION[QUERY]) == 0)
    {
        char *isfound = findNodeKey(*head, user_input[1]);
   
        if (strcmp(isfound, "EMPTY") != 0)
        {
            printf("A record of Key=%s, Value=%s is found in the database.\n", user_input[1], isfound);
        }
        else if (strcmp(isfound, "EMPTY") == 0)
        {
            printf("There is no record with Key=%s found in the database\n", user_input[1]);
        }
   
    }else  {
        PRINT_INVAILD_INSTRUCTION();
    }
    
}


void updateInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter == 2 && strcmp(user_input[0], DB_INSTRUCTION[UPDATE]) == 0)
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
   
    }else  {
        PRINT_INVAILD_INSTRUCTION();
    }
    
}

void deleteInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter == 1 && strcmp(user_input[0], DB_INSTRUCTION[DELETE]) == 0)
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
        
        
       
    }else  {
        PRINT_INVAILD_INSTRUCTION();
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
        return "Unable to get Working Directory Path";
    }
    
    
}

char* printWorkingDirectory(void){
    
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


void saveInstruction(char *user_input[], int counter, KeyValueNode **head) {
    
    if (counter == 1 && strcmp(user_input[0], DB_INSTRUCTION[SAVE]) == 0)
    {
        saveFromFile(getWorkingDirectory(user_input[1]), head);
        printf("SAVE Data to this file %s\n", user_input[1]);
    } else {
        PRINT_INVAILD_INSTRUCTION();
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
                openInstruction(user_input, counter, head);
            } else if (instructionType == HELP) {
                helpInstruction(db_State, counter);
            } else if (instructionType == EXIT) {
                return exitInstruction(user_input, counter);
            } else {
                PRINT_INVAILD_INSTRUCTION();
            }
            break;
        case DB_OPEN:
            switch (instructionType) {
                case SHOW:
                    showAllInstruction(user_input, counter, head);
                    break;
                case EXIT:
                    return exitInstruction(user_input, counter);
                    break;
                case INSERT:
                    insertInstruction(user_input, counter, head);
                    break;
                case QUERY:
                    queryInstruction(user_input, counter, head);
                    break;
                case HELP:
                    helpInstruction(db_State, counter);
                    break;
                case UPDATE:
                    updateInstruction(user_input, counter, head);
                    break;
                case DELETE:
                    deleteInstruction(user_input, counter, head);
                    break;
                case SAVE:
                    saveInstruction(user_input, counter, head);
                    break;
                case BACK:
                    db_State = DB_CLOSE;
                    break;
                default:
                    PRINT_INVAILD_INSTRUCTION();
                    break;
            }
            break;
        }
        
    return 0;
    
}

char *removeSpace(char *user_input)
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

int readFromFile(const char *filename, KeyValueNode **mainHead, char *user_input)
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
        printf("Unable to Open File Name : %s\n", user_input);
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
                tmp = createNode(removeSpace(key), removeSpace(value));
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
