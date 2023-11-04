//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"

// Structure to represent DB instruction
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

// Create instance of DB instruction list
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


char* file_Dir = "/Users/jagatees/Desktop/Files/Github_Hubs/Console_ChatBot/C_Console_Chat_Bot/EzDB/EzDB/Country.txt";



// Handle Database instruction based on user input
int logic_database(char *inv[], int inc, node_t **head){

    // No User Input , Display Empty Input
    if (inv[0] == NULL) {
        printf("Empty Input");
        return 0;
    }
    // Check User Input Match Instruction SHOW ALL
    if (inc >= 2 && strcmp(inv[0], db_instruction.SHOW) == 0 && strcmp(inv[1], db_instruction.ALL) == 0)
    {
        printf("There are in total %i records found: \n" ,list_node(*head));
        printlist(*head);
        return 0;
    }
    // Check User Input Match Instruction INSERT
    if (strcmp(inv[0], db_instruction.INSERT) == 0)
    {
        int isfound = find_node(*head, inv[1]);
        
        if (isfound == 1) {
            printf("The record with Key=%s already exists in the database\n", inv[1]);
        } else if (isfound == 0){
            node_t *tmp = create_new_node(inv[1], inv[2]);
            insert_at_head(head, tmp);
            printf("A new record of Key=%s Value=%s is successfully inserted\n", inv[1], inv[2]);
        }
        
        return 0;
    }
    // Check User Input Match Instruction QUERY
    else if (strcmp(inv[0], db_instruction.QUERY) == 0)
    {
        
        char *isfound = find_node_return_string(*head, inv[1]);
      
        if (strcmp(isfound, "EMPTY") != 0) {
            printf("A record of Key=%s, Value= %s is found in the database.\n", inv[1], isfound);
        } else if (strcmp(isfound, "EMPTY") == 0){
            printf("There is no record with Key=%s found in the database\n", inv[1]);
        }
        
        
        return 0;
    }
    // Check User Input Match Instruction UPDATE
    else if (strcmp(inv[0], db_instruction.UPDATE) == 0)
    {
        
        int isfound = find_node(*head, inv[1]);
        
        if (isfound == 1) {
            update_node(*head, inv[1], inv[2]);
            printf("The value for the record of Key=%s is successfully updated.\n", inv[1]);
        } else if (isfound == 0){
            printf("There is no record with Key=%s found in the database.\n", inv[1]);
        }
        
        return 0;
    }
    // Check User Input Match Instruction DELETE
    else if (strcmp(inv[0], db_instruction.DELETE) == 0) // DELETE INSTRUCTION
    {
        
        printf("The record of Key=%s is successfully deleted.", inv[1]);
        delete_node(head, inv[1]);
        return 0;
    }
    // Check User Input Match Instruction OPEN
    else if (strcmp(inv[0], db_instruction.OPEN) == 0) // DELETE INSTRUCTION
    {
        readFromFile(file_Dir, head);
        return 0;
    }
    // Check User Input Match Instruction SAVE
    else if (strcmp(inv[0], db_instruction.SAVE) == 0) // DELETE INSTRUCTION
    {
        saveFromFile(head, file_Dir);
        return 0;
    }
    // Check User Input Match Instruction EXIT
    else if (strcmp(inv[0], db_instruction.EXIT) == 0) // DELETE INSTRUCTION
    {
        printf("Exit EzDB\n");
        return 1;
    }
    // Check User Input Match Instruction HELP
    else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
    {
        printf("--------------INSTRUCTION LIST--------------\nSHOW ALL \t\t\t : PRINT OUT TABLE\nINSERT [Key] [Value] : Insert Into Table\nQuery [Key] \t\t : Display Data from table\nUPDATE [Key] [Value] : Update a value in the table\nDELETE [Key] \t\t : remove key from table\nOPEN [filename.txt]  : load data from file into cache\nSAVE [filename.txt]  : save data from cache into .txt\n");
        return 0;
    }
    // Invaild Instruction
    else {
        printf("instruction not found : %s\n", inv[0]);
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
   
    FILE *file = fopen(filename, "r");
    node_t *head = NULL;
    node_t *tmp;
    
    if (!file) {
        perror("Error opening file");
    }
 
    char line[1024];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // change this based on u want " " Space or "\t" for tab space in between
        char *key = strtok(line, " ");
        char *value = strtok(NULL, " ");
        
        if (key && value) {
            tmp = create_new_node(rtrim(key), rtrim(value));
            head = insert_at_head(&head, tmp);
            *mainHead = head;
        }
    }

    fclose(file);
}


void saveFromFile(node_t **head, const char *filename) {
    
    node_t *temporary = *head;
    
    printf("Keys :  Value \n");
    
    FILE *file = fopen(filename, "w");

    fprintf(file, "%s\t%s\n", "Key", "Value");

    while (temporary != NULL) {
        fprintf(file, "%s %s\n", temporary->key, temporary->value);

        temporary = temporary->next;
    }
    
    fclose(file);

    
}
