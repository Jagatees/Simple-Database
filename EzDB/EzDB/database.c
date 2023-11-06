//
//  database.c
//  EzDB
//
//  Created by Jagateesvaran on 25/10/23.
//

#include "database.h"

// Structure to represent DB instruction
struct DB
{
    const char *SHOW;
    const char *INSERT;
    const char *QUERY;
    const char *UPDATE;
    const char *DELETE;
    const char *ALL;
    const char *OPEN;
    const char *SAVE;
    const char *EXIT;
    const char *HELP;
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


int isOPEN = 0;


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


int databaseLogic(char *inv[], int inc, node_t **head)
{
    if (inv[0] == NULL)
    {
        printf("Empty Input\n");
        return 0;
    }
    // Check User Input Match Instruction EXIT
    else if (strcmp(inv[0], db_instruction.EXIT) == 0) // DELETE INSTRUCTION
    {
        printf("Exit Database\n");
        return 1;
    }
    if (isOPEN == 1)
    {
        // Check User Input Match Instruction SHOW ALL
        if (inc >= 2 && strcmp(inv[0], db_instruction.SHOW) == 0 && strcmp(inv[1], db_instruction.ALL) == 0 && isOPEN == 1)
        {
            printf("There are in total %i records found: \n", list_node(*head));
            printlist(*head);
            return 0;
        }
        // Check User Input Match Instruction INSERT
        else if (strcmp(inv[0], db_instruction.INSERT) == 0 && isOPEN == 1)
        {
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

            return 0;
        }
        // Check User Input Match Instruction QUERY
        else if (strcmp(inv[0], db_instruction.QUERY) == 0 && isOPEN == 1)
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

            return 0;
        }
        // Check User Input Match Instruction UPDATE
        else if (strcmp(inv[0], db_instruction.UPDATE) == 0 && isOPEN == 1)
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

            return 0;
        }
        // Check User Input Match Instruction DELETE
        else if (strcmp(inv[0], db_instruction.DELETE) == 0 && isOPEN == 1) // DELETE INSTRUCTION
        {

            printf("The record of Key=%s is successfully deleted.\n", inv[1]);
            delete_node(head, inv[1]);
            return 0;
        }
        // Check User Input Match Instruction OPEN

        // Check User Input Match Instruction SAVE
        else if (strcmp(inv[0], db_instruction.SAVE) == 0 && isOPEN == 1) // DELETE INSTRUCTION
        {
            printf("SAVE Data to this file %s\n", inv[1]);

            char cwd[MAX_PATH_LEN];
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
            return 0;
        }
        // Check User Input Match Instruction HELP
        else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
        {
            printf("--------------INSTRUCTION LIST--------------\nSHOW ALL \t\t\t : PRINT OUT TABLE\nINSERT [Key] [Value] : Insert Into Table\nQuery [Key] \t\t : Display Data from table\nUPDATE [Key] [Value] : Update a value in the table\nDELETE [Key] \t\t : remove key from table\nSAVE [filename.txt]  : save data from cache into .txt\n");
            return 0;
        }
        // Invaild Instruction
    }
    else if (isOPEN == 0)
    {
        if (strcmp(inv[0], db_instruction.OPEN) == 0) // DELETE INSTRUCTION
        {
            char cwd[MAX_PATH_LEN];
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

            if (strcmp(inv[1], "Color.txt") == 0)
            {
                readFromFile(cwd, head);
                printf("Save Key & Values into cahe from %s\n", inv[1]);
                isOPEN = 1;
            }
            else
            {
                isOPEN = 0;
                printf("Unable to find %s at location\n", inv[1]);
            }
            return 0;
        }
        // Check User Input Match Instruction HELP
        else if (strcmp(inv[0], db_instruction.HELP) == 0) // DELETE INSTRUCTION
        {
            printf("--------------INSTRUCTION LIST--------------\nOPEN [filename.txt]  : load data from file into cache\n");
            return 0;
        }
        else
        {
            printf("Please Load in a .txt file first before entering into database\n");
        }
    }
    else
    {
        printf("instruction not found : %s\n", inv[0]);
        return 0;
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

void readFromFile(const char *filename, node_t **mainHead)
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
        perror("Error opening file");
    }

    char line[1024];
    fgets(line, sizeof(line), file);

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
