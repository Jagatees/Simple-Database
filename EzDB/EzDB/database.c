//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"

struct DB {
    const char* SHOW;
    const char* INSERT;
    const char* QUERY;
    const char* UPDATE;
    const char* DELETE;
    const char* ALL;
    const char* OPEN;
    const char* SAVE;
    const char* EXIT;
    const char* HELP;
};

struct DB db_instruction = {
    .SHOW = "SHOW",
    .ALL = "ALL",
    .INSERT = "INSERT",
    .QUERY = "QUERY",
    .UPDATE = "UPDATE",
    .DELETE = "DELETE",
    .OPEN = "OPEN",
    .SAVE = "SAVE",
    .EXIT = "EXIT",
    .HELP = "HELP",
};



// inv is the list of user input string and inc is the counter length
int logic_databse(char *inv[], int inc, node_t **head){    
    if (inv[0] == NULL) {
        printf("U Enter Nothing So we are kicking u out .\n");
        return 1;
    }
    if (inc >= 2 && strcmp(inv[0], db_instruction.SHOW) == 0 && strcmp(inv[1], db_instruction.ALL) == 0) // SHOW ALL INSTRUCTION
    {
        printf("Welcome to SHOW ALL Instruction\n");
        printlist(*head);
        return 0;
    }
    if (strcmp(inv[0], db_instruction.INSERT) == 0)
    {
        printf("Welcome to INSERT Instruction\n");
        
        // 1 = FOUND
        // 0 = NOT FOUND
        
        int isfound = find_node(*head, inv[1]);
        
        if (isfound == 1) {
            printf("The record with Key=%s already exists in the database\n", inv[1]);
        } else if (isfound == 0){
            // need do some error handling user the 2 value is not a right type
            node_t *tmp = create_new_node(inv[1], inv[2]);
            insert_at_head(head, tmp);
            printf("A new record of Key=%s Value=%s is successfully inserted\n", inv[1], inv[2]);
        }
        
        return 0; // to say if we still in the game
    }
    else if (strcmp(inv[0], db_instruction.QUERY) == 0) // QUERY INSTRUCTION
    {
        printf("Welcome to QUERY Instruction\n");

        
        int isfound = find_node(*head, inv[1]);
        
        // CHANGE SO IT CAN PRINT OUT THE VALUE FOR THE KEY
        if (isfound == 1) {
            printf("A record of Key=%s, Value= {missing value} is found in the database.\n", inv[1]);
        } else if (isfound == 0){
            printf("There is no record with Key=%s found in the database\n", inv[1]);
        }
        
        
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.UPDATE) == 0) // UPDATE INSTRUCTION
    {
        printf("Welcome to UPDATE Instruction\n");
        
        int isfound = find_node(*head, inv[1]);
        
        if (isfound == 1) {
            update_node(*head, inv[1], inv[2]);
            printf("The value for the record of Key=%s is successfully updated.\n", inv[1]);
        } else if (isfound == 0){
            printf("There is no record with Key=%s found in the database.\n", inv[1]);
        }
        
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.DELETE) == 0) // DELETE INSTRUCTION
    {
        printf("Welcome to DELETE Instruction\n");
        delete_node(head, inv[1]);
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.OPEN) == 0) // DELETE INSTRUCTION
    {
        printf("Welcome to OPEN from database Instruction\n");
        const char *database_file = "/Users/jagatees/Desktop/Files/Github_Hubs/Console_ChatBot/C_Console_Chat_Bot/EzDB/EzDB/test2.txt";
        readFromFile(database_file, head);

        return 0;
    }
    else if (strcmp(inv[0], db_instruction.SAVE) == 0) // DELETE INSTRUCTION
    {
        printf("Welcome to SAVE to database Instruction\n");
        saveFromFile(head);
        
        
       
        return 0;
    }
    else if (strcmp(inv[0], db_instruction.EXIT) == 0) // DELETE INSTRUCTION
    {
        printf("Disconnected from J_Database...\n");
        return 1;
    }
    else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
    {
        printf("--------------INSTRUCTION LIST--------------\nSHOW ALL \t\t\t : PRINT OUT TABLE\nINSERT [Key] [Value] : Insert Into Table\nQuery [Key] \t\t : Display Data from table\nUPDATE [Key] [Value] : Update a value in the table\nDELETE [Key] \t\t : remove key from table\nOPEN [filename.txt]  : load data from file into cache\nSAVE [filename.txt]  : save data from cache into .txt\n");
        return 0;
    }
    else {
        printf("I don't understand this command %s\n", inv[0]);
        return 0;
    }

    return 0;
    
}


char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

void readFromFile(const char *filename, node_t **mainHead) {
    node_t *head = NULL;
    node_t *tmp;
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        perror("Error opening file");
    }
 
    char line[1024];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "\t");
        char *value = strtok(NULL, "\t");
        
        if (key && value) {
            tmp = create_new_node(rtrim(key), rtrim(value));
            head = insert_at_head(&head, tmp);
            *mainHead = head;
        }
    }

    fclose(file);
}


void saveFromFile(node_t **head) {
    
    node_t *temporary = *head;
    
    printf("Keys :  Value \n");
    
    const char *database_file = "/Users/jagatees/Desktop/Files/Github_Hubs/Console_ChatBot/C_Console_Chat_Bot/EzDB/EzDB/test2.txt";
    FILE *file = fopen(database_file, "w");

    fprintf(file, "%s\t%s\n", "Key", "Value");

    while (temporary != NULL) {
        fprintf(file, "%s\t%s\n", temporary->key, temporary->value);

        temporary = temporary->next;
    }
    
    fclose(file);

    
}
